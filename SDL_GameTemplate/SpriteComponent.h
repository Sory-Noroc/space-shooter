#pragma once
#include "Components.h"
#include "SDL.h"
#include "TextureManager.h"

class SpriteComponent : public Component
{
private:
	PositionComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;
	SDL_Renderer* renderer;

public:
	SpriteComponent() = default;
	SpriteComponent(const char* path)
	{
		texture = TextureManager::LoadTexture(path);
		this->renderer = renderer;
	}
	
	void init() override
	{
		transform = &entity->getComponent<PositionComponent>();

		srcRect.x = srcRect.y = 0;
		srcRect.w = 80;
		srcRect.h = 80;
		destRect.w = destRect.h = 80;
	}

	void update() override
	{
		destRect.x = (int)transform->position.x;
		destRect.y = (int)transform->position.y;
	}

	void draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect);
	}
};