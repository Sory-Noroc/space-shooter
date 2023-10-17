#pragma once
#include "Component.h"
#include <SDL.h>

class Spaceship : public Component
{
	SDL_Texture* texture{};
	SDL_Renderer* renderer{};
	SDL_Rect srcRect{}, destRect{};

public:
	Spaceship() = default;
	Spaceship(const char* path, SDL_Renderer* renderer);

	void setTex(const char* path);

	void init() override;

	void update() override;

	void draw() override;

	void moveLeft(int step);

	void moveRight(int step);
};
