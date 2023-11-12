#pragma once
#include "Components.h"
#include "Vector2D.h"

class PositionComponent : public Component {

public:
	Vector2D position;
	Vector2D velocity;

	int speed = 3;


	PositionComponent() {
		position.x = 0.0f;
		position.y = 0.0f;
	}

	PositionComponent(float x, float y)
	{
		position.x = x;
		position.y = y;
	}

	void init() override {
		velocity.x = 0;
		velocity.y = 0;
	}

	void update() override
	{
		if (position.x + velocity.x * speed >= 0 && position.x + velocity.x * speed <= SCREEN_WIDTH - 75)
		{
			position.x += velocity.x * speed;
		}
		if (position.y + velocity.y * speed >= 0 && position.y + velocity.y * speed <= SCREEN_HEIGHT - 120)
		{
			position.y += velocity.y * speed;
		}
	}
};