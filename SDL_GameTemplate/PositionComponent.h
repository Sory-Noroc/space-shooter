#pragma once
#include "Components.h"
#include "Game.h"
#include "Vector2D.h"

class PositionComponent : public Component {

public:
	Vector2D position;
	Vector2D velocity;

	int height = 24;
	int width = 16;
	int scale = 1;
	int speed = 3;

	bool deleteOnEdge = false;

	PositionComponent() {
		position.x = 0.0f;
		position.y = 0.0f;
	}

	PositionComponent(int scale) {
		this->scale = scale;
		position.x = 0.0f;
		position.y = 0.0f;
	}

	PositionComponent(float x, float y)
	{
		position.x = x;
		position.y = y;
	}

	PositionComponent(float x, float y, int width, int height)
	{
		position.x = x;
		position.y = y;
		this->width = width;
		this->height = height;
	}

	PositionComponent(float x, float y, int width, int height, bool deleteOnEdge) {
		position.x = x;
		position.y = y;
		this->width = width;
		this->height = height;
		this->deleteOnEdge = deleteOnEdge;
	}

	void init() override {
		velocity.x = 0;
		velocity.y = 0;
	}

	PositionComponent* setSpeed(int speed) { 
		this->speed = speed; 
		return this; 
	}
	PositionComponent* setScale(int scale) { 
		this->scale = scale; 
		return this; 
	}
	PositionComponent* setVelocity(Vector2D v) { 
		this->velocity = v; 
		return this; 
	}

	void update() override
	{
		if (position.x + velocity.x * speed >= 0 && position.x + velocity.x * speed <= SCREEN_WIDTH - (width * scale))
		{
			position.x += velocity.x * speed;
		} else if (deleteOnEdge == true)
		{
			entity->destroy();
		}

		if (position.y + velocity.y * speed >= 0 && position.y + velocity.y * speed <= SCREEN_HEIGHT - (height * scale))
		{
			position.y += velocity.y * speed;
		}
		else if (deleteOnEdge == true)
		{
			entity->destroy();
		}
	}
};

class ShipPositionComponent : public PositionComponent {
	
	ShipPositionComponent(int scale) : PositionComponent(scale) {
		this->scale = scale;
		position.x = 0.0f;
		position.y = 0.0f;
	}

	void update() override {
		if (position.x + velocity.x * speed >= 0 && position.x + velocity.x * speed <= SCREEN_WIDTH - (width * scale))
		{
			position.x += velocity.x * speed;
		}
		if (position.y + velocity.y * speed >= 0 && position.y + velocity.y * speed <= SCREEN_HEIGHT - (height * scale))
		{
			position.y += velocity.y * speed;
		}
	}
};

class BulletPositionComponent : public PositionComponent {
	void update() override {
		// Todo
	}
};