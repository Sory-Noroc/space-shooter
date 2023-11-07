#include "TextureManager.h"
#include "Game.h"
#include "SDL.h"
#include "SDL_image.h"

SDL_Texture* TextureManager::LoadTexture(const char* fileName)
{
	SDL_Surface* tempSurface = IMG_Load(fileName);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
	SDL_FreeSurface(tempSurface);
	return tex;
}

void TextureManager::Draw(SDL_Texture * tex, SDL_Rect src, SDL_Rect dest)
{
   // sent with nullptr
	SDL_RenderCopy(Game::renderer, tex, &src, &dest);
}
