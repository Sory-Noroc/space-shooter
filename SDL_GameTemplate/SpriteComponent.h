#pragma once
#include "Components.h"
#include "TextureManager.h"

class SpriteComponent : public Component
{
private:
	PositionComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;
	SDL_Renderer* renderer;
	bool animated = false;
	int imageCols = 0, imageRows = 0;
	int speed = 200;  // delay in ms between animations

public:
	SpriteComponent() = default;
	SpriteComponent(const char* path)
	{
		texture = TextureManager::LoadTexture(path);
		this->renderer = renderer;
	}

	SpriteComponent(const char* path, int mSpeed, int imageColumns, int imageRows)
	{
		animated = true;
		this->imageCols = imageColumns;
		this->imageRows = imageRows;
		this->speed = mSpeed;
		this->texture = TextureManager::LoadTexture(path);
		this->renderer = renderer;
	}

	~SpriteComponent() {
		SDL_DestroyTexture(texture);
	}

	SDL_Rect getImageRect() {
		return destRect;
	}
	
	void init() override
	{
		transform = &entity->getComponent<PositionComponent>();

		srcRect.x = srcRect.y = 0;
		srcRect.w = transform->width;
		srcRect.h = transform->height;
		destRect.w = transform->width * transform->scale;
		destRect.h = transform->height * transform->scale;
		destRect.x = (int)transform->position.x;
		destRect.y = (int)transform->position.y;
	}

	void update() override
	{
		if (animated) {
			int sprite_tick = static_cast<int>((SDL_GetTicks() / speed) % (imageRows * imageCols));
			if (sprite_tick >= imageCols) {
				srcRect.y = srcRect.h;
			}
			else {
				srcRect.y = 0;
			}
			srcRect.x = srcRect.w * (sprite_tick % imageCols);
		}


		destRect.x = (int)transform->position.x;
		destRect.y = (int)transform->position.y;
	}

	void draw() override
	{
		TextureManager::Draw(texture, &srcRect, &destRect);
	}
};