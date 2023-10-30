#pragma once
#include "Components.h"
#include "Vector2D.h"

struct PositionComponent : public Component {

public:
	Vector2D position;

	PositionComponent() {
		position.x = 0.0f;
		position.y = 0.0f;
	}

	PositionComponent(float x, float y)
	{
		position.x = x;
		position.y = y;
	}

	void update() override
	{
	}
};