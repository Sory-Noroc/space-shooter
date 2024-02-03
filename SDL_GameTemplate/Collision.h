#pragma once
#include "SDL.h"

class ColliderComponent;
class Collision {
public:
	static bool AABB(const SDL_Rect& rectA, const SDL_Rect& rectB);
	static bool AABB(ColliderComponent& collA, ColliderComponent& collB);
};