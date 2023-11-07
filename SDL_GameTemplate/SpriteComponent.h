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
	bool animated = false;
	int frames = 0;
	int speed = 100;  // delay in ms between animations

public:
	SpriteComponent() = default;
	SpriteComponent(const char* path)
	{
		texture = TextureManager::LoadTexture(path);
		this->renderer = renderer;
	}

	SpriteComponent(const char* path, int nFrames, int mSpeed)
	{
		animated = true;
		frames = nFrames;
		speed = mSpeed;
		texture = TextureManager::LoadTexture(path);
		this->renderer = renderer;
	}
	
	void init() override
	{
		transform = &entity->getComponent<PositionComponent>();

		srcRect.x = srcRect.y = 0;
		srcRect.w = 16;
		srcRect.h = 24;
		destRect.w = 16 * 5;
		destRect.h = 24 * 5;
	}

	void update() override
	{
		if (animated) {
			int sprite_tick = static_cast<int>((SDL_GetTicks() / speed) % frames);
			if (sprite_tick >= 5) {
				srcRect.y = srcRect.h;
			}
			else {
				srcRect.y = 0;
			}
			srcRect.x = srcRect.w * (sprite_tick % 5);
		}


		destRect.x = (int)transform->position.x;
		destRect.y = (int)transform->position.y;
	}

	void draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect);
	}
};