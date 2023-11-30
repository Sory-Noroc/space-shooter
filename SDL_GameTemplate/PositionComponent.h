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

	bool outOfBounds = false;

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

	void init() override {
		velocity.x = 0;
		velocity.y = 0;
	}

	void update() override
	{
		if (position.x + velocity.x * speed >= 0 && position.x + velocity.x * speed <= SCREEN_WIDTH - (width * scale))
		{
			position.x += velocity.x * speed;
		} else 
		{
			outOfBounds = true;
		}
		if (position.y + velocity.y * speed >= 0 && position.y + velocity.y * speed <= SCREEN_HEIGHT - (height * scale))
		{
			position.y += velocity.y * speed;
		}
		else
		{
			outOfBounds = true;
		}
	}
};