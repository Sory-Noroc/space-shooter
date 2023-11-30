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
	int delay = 1000;

public:
	BulletManagerComponent() = default;
	BulletManagerComponent(int delay, float velocity){
		// Delay between the bullets being shot
		this->delay = delay;
		// IF Velocity is 1 => moving down
		this->velocity.y = velocity;
		imageSizes[0] = Vector2D(32, 32);
	}

	void init() override {
		sprite = &entity->getComponent<SpriteComponent>();
		position = &entity->getComponent<PositionComponent>();
		
	}

	void activate() { active = true; }
	void deactivate() { active = false; }

	void setStartPosition() {
		SDL_Rect temp = sprite->getImageRect();
		startPos.y = temp.y;
		startPos.x = temp.x + temp.w / 2.;
	}

	void makeBullet() {
		setStartPosition();
		Entity *bullet = &addEntity();
		bullet->addComponent<PositionComponent>(startPos.x, startPos.y, imageSizes[0].x, imageSizes[0].y).velocity = this->velocity;
		bullet->getComponent<PositionComponent>().speed = 1;
		bullet->addComponent<SpriteComponent>("assets/laser-bolts.png", 50, 2, 1);
	}

	void update() override {
		Manager::update();
	}

	void draw() override {
		Manager::draw();
	}
};
