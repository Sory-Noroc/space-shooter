#include "TextureManager.h"
#include "Game.h"
#include "SDL.h"

SDL_Texture* TextureManager::LoadTexture(const char* fileName)
{
	SDL_Surface* tempSurface = IMG_Load(fileName);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
	SDL_FreeSurface(tempSurface);
	return tex;
}

SDL_Texture* TextureManager::LoadTexture(SDL_Surface* surface) {
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, surface);
	return tex;
}

void TextureManager::Draw(SDL_Texture * tex, SDL_Rect *src, SDL_Rect *dest)
{
   // sent with nullptr
	SDL_RenderCopy(Game::renderer, tex, src, dest);
}
