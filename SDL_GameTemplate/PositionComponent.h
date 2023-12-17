#pragma once
#include "Components.h"
#include "Game.h"
#include "Vector2D.h"

// enum OnEdge {ignore, stop};

class PositionComponent : public Component {

public:
	Vector2D position;
	Vector2D velocity;

	int height = 24;
	int width = 16;
	int scale = 1;
	int speed = 3;

	OnEdge actionEdge = OnEdge(ignore);

	PositionComponent() {
		position.x = 0.0f;
		position.y = 0.0f;
	}

	PositionComponent(int scale, OnEdge action) {
		this->scale = scale;
		position.x = 0.0f;
		position.y = 0.0f;
		this->actionEdge = action;
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

	PositionComponent(float x, float y, int width, int height, OnEdge actOnEdge) {
		position.x = x;
		position.y = y;
		this->width = width;
		this->height = height;
		this->actionEdge = actOnEdge;
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
		// start: -x, -y
		// dimensions: 3 * width, 3 * height
		if (actionEdge == stop) {
			if (position.x + velocity.x * speed >= 0 &&
					position.x + velocity.x * speed <= SCREEN_WIDTH - (width * scale))
			{
				position.x += velocity.x * speed;
			}

			if (position.y + velocity.y * speed >= 0 &&
					position.y + velocity.y * speed <= SCREEN_HEIGHT - (height * scale))
			{
				position.y += velocity.y * speed;
			}
		}

		if (actionEdge == ignore) {
			if (position.x + velocity.x * speed >= -SCREEN_WIDTH &&
				position.x + velocity.x * speed <= 2 * SCREEN_WIDTH - (width * scale))
			{
				position.x += velocity.x * speed;
			}
			else {
				entity->destroy();
			}
		}

		if (actionEdge == ignore) {
			if (position.y + velocity.y * speed >= -SCREEN_HEIGHT &&
					position.y + velocity.y * speed <= 2 * SCREEN_HEIGHT - (width * scale))
			{
				position.y += velocity.y * speed;
			}
			else {
				entity -> destroy();
			}
		}
	}
};