#pragma once
#include "ECS.h"
#include "entityData.h"
#include "TextureManager.h"

class Animation: public Component {
	SDL_Rect srcRect, destRect;
	SDL_Texture* texture = nullptr;
	int delay, m = 0, n = 0;
	float prev = 0, current = 0;
	entityData sprite;

public:
	Animation(int x, int y, entityData sprite) {
		this->sprite = sprite;
		this->delay = sprite.spriteDelay;
		texture = TextureManager::LoadTexture(sprite.path);

		srcRect.w = sprite.w;
		srcRect.h = sprite.h;
		destRect.x = x;
		destRect.y = y;
		destRect.w = srcRect.w * sprite.scale;
		destRect.h = srcRect.h * sprite.scale;
	}

public: 
	void draw() {
		current = static_cast<float>(SDL_GetTicks());
		TextureManager::Draw(texture, &srcRect, &destRect);
		if (current - prev >= delay) {
			srcRect.x = n * srcRect.w;
			srcRect.y = m * srcRect.h;
			if (n == sprite.spriteCols) {
				// If n is past the last column
				if (m == sprite.spriteRows) {
					// If we are out of both rows and columns
					entity->destroy();
					return;
				}
				else {
					// Else we got more rows to animate
					m++;
					n = 0;
				}
			}
			else {
				// Else we navigate the columns
				n++;
			}
			prev = current;
		}
	}

	~Animation() {
		SDL_DestroyTexture(texture);
	}
};