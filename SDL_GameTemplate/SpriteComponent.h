#pragma once
#include "Components.h"
#include "SDL.h"
#include "TextureManager.h"

class SpriteComponent : public Component
{
private:
	PositionComponent* position;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;
	SDL_Renderer* renderer;

public:
	SpriteComponent() = default;
	SpriteComponent(const char* path, SDL_Renderer* renderer)
	{
		texture = TextureManager::LoadTexture(path, renderer);
		this->renderer = renderer;
	}
	
	void init() override
	{
		position = &entity->getComponent<PositionComponent>();

		srcRect.x = srcRect.y = 0;
		destRect.x = 350;
		destRect.y = 500;
		srcRect.w = srcRect.h = 50;
		destRect.w = destRect.h = 80;
	}

	void update() override
	{
		destRect.x = position->x();
		destRect.y = position->y();
	}

	void draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect, renderer);
	}

};