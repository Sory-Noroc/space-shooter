#include "Collision.h"

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