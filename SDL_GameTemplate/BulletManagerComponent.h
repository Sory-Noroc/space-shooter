#pragma once
#include "Components.h"
#include "Vector2D.h"
#include "entityData.h"
#include "Animation.h"

class BulletManagerComponent : public Component, public Manager {

	bool active = false;
	Entity* shooter = entity;
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
	}

	void activate() { active = true; }
	void deactivate() { active = false; }

	void setStartPosition(float orientation) {
		SDL_Rect image = shooterSprite->getImageRect();
		startPos.x = image.x + image.w / 2.f - (bulletData[imageIndex].w * scale) / 2.f;
		
		if (orientation == -1)
		{
			startPos.y = image.y - (bulletData[imageIndex].h * scale);
		}
		else 
		{
			startPos.y = image.y + image.h;
		}
	}

	void makeBullet() {
		setStartPosition(velocity.y);
		Entity *bullet = &addEntity();
		entityData shot = bulletData[imageIndex];
		bullet->addComponent<PositionComponent>(startPos.x, startPos.y, shot.w, shot.h, ignore)
			.setSpeed(2)->setScale(scale)->setVelocity(velocity);
		bullet->addComponent<SpriteComponent>(shot.path, shot.spriteDelay, shot.spriteCols, shot.spriteRows);
		bullet->addComponent<ColliderComponent>(tag::bullet);
	}

	void checkCollisions() {
		for (auto& bullet : entities) {
			// for each bullet
			for (auto& ship : entity->manager->entities) {
				if (Collision::AABB(bullet->getComponent<ColliderComponent>().getCollider(), ship->getComponent<ColliderComponent>().getCollider())) {
					ship->destroy();
				}
			}
		}
	}

	void update() override {
		int currentTime = SDL_GetTicks();
		if (active && (currentTime - previousTime) > delay) {
			makeBullet();
			previousTime = currentTime;
		}
		checkCollisions();
		Manager::refresh();
		Manager::update();
	}

	void draw() override {
		Manager::draw();
	}
};
