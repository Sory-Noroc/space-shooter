#pragma once
#include <string>
#include "SDL.h"
#include "ECS.h"
#include "Components.h"
#include "Collision.h"

class ColliderComponent : public Component {
	int tag;
	SDL_Rect collider;
	PositionComponent* transform;

public:
	ColliderComponent(int tag) {
		this->tag = tag;
	}

	void init() override {
		transform = &entity->getComponent<PositionComponent>();
	}

	void update() override {
		collider.x = static_cast<int>(transform->position.x);
		collider.y = static_cast<int>(transform->position.y);
		collider.w = transform->width * transform->scale;
		collider.h = transform->height * transform->scale;

	}

	SDL_Rect getCollider() {
		return collider;
	}
};
