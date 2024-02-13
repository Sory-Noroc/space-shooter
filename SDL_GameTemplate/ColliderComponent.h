#pragma once
#include <string>
#include <algorithm>
#include "SDL.h"
#include "ECS.h"
#include "Collision.h"
#include "Components.h"

enum tag { champ, champBullet, enemy, enemyBullet };

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
		Game::colliders.emplace_back(this);
	}

	void update() override {
		collider.x = static_cast<int>(transform->position.x);
		collider.y = static_cast<int>(transform->position.y);
		collider.w = transform->width * transform->scale;
		collider.h = transform->height * transform->scale;
	}

	bool is_colliding(ColliderComponent &other) {
		if (Collision::AABB(this->getCollider(), other.getCollider()) &&
			!isSame(other)) {
			return true;
		}
		return false;
	}

	bool isSame(ColliderComponent& other) {
		return this->tag == other.tag || getAntiTag() == other.tag;
	}

	enum tag getAntiTag() {
		switch (tag) {

		case enemy: return enemyBullet;
		case champ: return champBullet;

		case enemyBullet: return enemy;
		case champBullet: return champ;

		default: return enemyBullet;
		}
	}

	SDL_Rect getCollider() {
		return collider;
	}

	~ColliderComponent() {
		if (!Game::colliders.empty()) {
			Game::eraseCollider(this);
		}
	}
};
