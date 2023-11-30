#pragma once
#include <string>
#include "SDL.h"
#include "ECS.h"
#include "Components.h"

class ColliderComponent : public Component {
	SDL_Rect collider;
	std::string tag;

	PositionComponent* transform;

	void init() override {
		if (!entity->hasComponent<PositionComponent>()) {
			entity->addComponent<PositionComponent>();
		}
		transform = &entity->getComponent<PositionComponent>();
	}

	void update() override {
		collider.x = static_cast<int>(transform->position.x);
		collider.y = static_cast<int>(transform->position.y);
		collider.w = transform->width * transform->scale;
		collider.h = transform->height * transform->scale;
	}
};