#pragma once
#include "entityData.h"
#include "TextureManager.h"

class Animation {
public:
	static void draw(float x, float y, entityData sprite) {

		SDL_Rect srcRect, destRect;
		SDL_Texture* texture = TextureManager::LoadTexture(sprite.path);
		srcRect.x = 0;
		srcRect.y = 0;
		srcRect.w = sprite.w;
		srcRect.h = sprite.h;
		destRect.x = x;
		destRect.y = y;
		destRect.w = srcRect.w * sprite.scale;
		destRect.h = srcRect.h * sprite.scale;
		float prev = SDL_GetTicks() / sprite.spriteDelay;

		for (int i = 0; i < sprite.spriteRows; i++) {
			srcRect.y = i * sprite.h;
			for (int j = 0; j < sprite.spriteCols; j++) {
				srcRect.x = j * sprite.w;
				TextureManager::Draw(texture, srcRect, destRect);
			}
		}
		//SDL_DestroyTexture(texture);
	}
};