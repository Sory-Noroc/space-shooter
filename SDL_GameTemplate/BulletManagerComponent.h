#pragma once
#include "Components.h"
#include "Vector2D.h"

class BulletManagerComponent : public Component, public Manager {

	bool active = false;
	Entity* shooter = entity;
	Vector2D velocity, startPos;
	Vector2D* imageSizes = new Vector2D[10];
	SpriteComponent* sprite = nullptr;
	PositionComponent* position = nullptr;
	int previousTime = 0;
	int delay = 1000, imageIndex = 0, scale = 3;

public:
	BulletManagerComponent() = default;
	BulletManagerComponent(int delay, int scale, float velocity) {
		// Delay between the bullets being shot
		this->delay = delay;
		// IF Velocity is 1 => moving down
		this->velocity.y = velocity;
		this->scale = scale;
		imageSizes[0] = Vector2D(5, 5);
	}

	~BulletManagerComponent() {
		delete[] imageSizes;
	}

	void init() override {
		sprite = &entity->getComponent<SpriteComponent>();
		position = &entity->getComponent<PositionComponent>();
	}

	void activate() { active = true; }
	void deactivate() { active = false; }

	void setStartPosition() {
		SDL_Rect temp = sprite->getImageRect();
		startPos.y = temp.y - imageSizes[imageIndex].y;
		startPos.x = temp.x + temp.w / 2. - imageSizes[imageIndex].x * scale / 2.;
	}

	void makeBullet() {
		setStartPosition();
		Entity *bullet = &addEntity();
		bullet->addComponent<PositionComponent>(startPos.x, startPos.y, imageSizes[imageIndex].x, imageSizes[imageIndex].y, ignore)
			.setSpeed(1)->setScale(4);
		bullet->getComponent<PositionComponent>().setVelocity(this->velocity);
		bullet->addComponent<SpriteComponent>("assets/laser-bolts.png", 50, 2, 1);
	}

	void update() override {
		int currentTime = SDL_GetTicks();
		if (active && (currentTime - previousTime) > delay) {
			makeBullet();
			previousTime = currentTime;
		}
		Manager::refresh();
		Manager::update();
	}

	void draw() override {
		Manager::draw();
	}
};
