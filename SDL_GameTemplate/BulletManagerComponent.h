#pragma once
#include "Components.h"
#include "Vector2D.h"
#include "entityData.h"
#include "Animation.h"

class Game;

class BulletManagerComponent : public Component {
	int bulletCount = 0;
	bool active = false;
	Vector2D velocity, startPos;
	SpriteComponent* shooterSprite = nullptr;
	PositionComponent* shooterPosition = nullptr;
	int previousTime = 0;
	int delay = 1000, imageIndex = 0, scale = 0;

public:
	BulletManagerComponent() = default;
	BulletManagerComponent(int delay, int scale, float velocity, int imageIndex) {
		// Delay between the bullets being shot
		this->delay = delay;
		// IF Velocity is 1 => moving down
		this->velocity.y = velocity;
		this->imageIndex = imageIndex;
		this->scale = scale;
	}

	void init() override {
		shooterSprite = &entity->getComponent<SpriteComponent>();
		shooterPosition = &entity->getComponent<PositionComponent>();
	
		if (!shooterSprite || !shooterPosition) {
			std::cerr << "Error: Shooter sprite or position component not found." << std::endl;
		}
	}

	void activate() { active = true; }
	void deactivate() { active = false; }

	void setStartPosition(float orientation) {
		SDL_Rect image = shooterSprite->getImageRect();
		startPos.x = image.x + image.w / 2.f - (bulletData[imageIndex].w * scale) / 2.f;
		
		if (orientation == -1)
		{
			startPos.y = (float)(image.y - (bulletData[imageIndex].h * scale));
		}
		else 
		{
			startPos.y = (float)(image.y + image.h);
		}
	}

	void makeBullet() {
		Entity* bullet = new Entity(entity->manager);
		entity->manager.addEntityToQueue(bullet);
		entityData shot = bulletData[imageIndex];
		setStartPosition(velocity.y);
		bullet->health = shot.health;
		bullet->addComponent<PositionComponent>(startPos.x, startPos.y, shot.w, shot.h, ignore)
			.setSpeed(2)->setScale(scale)->setVelocity(velocity);
		bullet->addComponent<SpriteComponent>(shot.path, shot.spriteDelay, shot.spriteCols, shot.spriteRows);
		bullet->addComponent<ColliderComponent>(entity->getComponent<ColliderComponent>().getAntiTag());
	}

	void update() override {
		int currentTime = SDL_GetTicks();
		if (active && (currentTime - previousTime) > delay) {
			makeBullet();
			previousTime = currentTime;
		}
	}
};
