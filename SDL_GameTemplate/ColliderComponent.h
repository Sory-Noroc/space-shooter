#pragma once
#include <string>
#include "SDL.h"
#include "ECS.h"
#include <algorithm>
#include "Components.h"
#include "Collision.h"

class ColliderComponent : public Component {
	SDL_Rect collider;
	PositionComponent* transform;

public:
	int tag;
	ColliderComponent(int tag) {
		this->tag = tag;
	}

	void init() override {
		if (!entity->hasComponent<PositionComponent>())
		{
			throw "Must have PositionComponent before adding a ColliderComponent";
		}
		transform = &entity->getComponent<PositionComponent>();
		update(); // Set the collider to the correct position
		Game::colliders.push_back(this);
	}

	void update() override {
		collider.x = static_cast<int>(transform->position.x);
		collider.y = static_cast<int>(transform->position.y);
		collider.w = transform->width * transform->scale;
		collider.h = transform->height * transform->scale;
	}

	bool is_colliding(ColliderComponent other) {
		if (Collision::AABB(*this, other)) {
			return true;
		}
		return false;
	}

	SDL_Rect getCollider() {
		return collider;
	}
};
