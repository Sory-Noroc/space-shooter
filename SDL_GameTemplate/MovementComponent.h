#pragma once
#include "ECS.h"
#include "PositionComponent.h"
#include "Vector2D.h"

class Vector2D;

class MovementComponent : public Component {
	PositionComponent* posComp = nullptr;
	Vector2D velocity = Vector2D(1, 1);

public:
	void init() {
		if (entity->hasComponent<PositionComponent>()) {
			posComp = &entity->getComponent<PositionComponent>();
		}
	}

	void update() {
		if (!posComp->isInScreenX()) {
			velocity.x = -velocity.x;
		}
		posComp->position.x += velocity.x;
	}
};