#pragma once
#include <SDL_image.h>

class TextureManager
{
public:
	static SDL_Texture* LoadTexture(const char* fileName);
	static SDL_Texture* LoadTexture(SDL_Surface* surface);
   static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest);
};