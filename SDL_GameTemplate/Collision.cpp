#include "Collision.h"
#include "ColliderComponent.h"

bool Collision::AABB(const SDL_Rect& rectA, const SDL_Rect& rectB) {
	if (
		rectA.x + rectA.w >= rectB.x &&
		rectA.y + rectA.h >= rectB.y &&
		rectB.x + rectB.w >= rectA.x &&
		rectB.y + rectB.h >= rectA.y
		) {
		return true;
	}
	return false;
}

bool Collision::AABB(ColliderComponent& collA, ColliderComponent& collB) {
	if (AABB(collA.getCollider(), collB.getCollider()) &&
		collA.tag != collB.tag) {
		return true;
	}
	return false;
}