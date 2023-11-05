#include "Background.h"
#include "TextureManager.h"
#include "Game.h"
#include "SDL.h"

Background::Background(SDL_Renderer* renderer)
{
	this->renderer = renderer;
	space = TextureManager::LoadTexture("assets/space.png");

	src.x = 0;
	src.y = 0;
	src.w = 800;
	src.h = 640;
	dest.x = 0;
	dest.y = 0;
	dest.w = 800;
	dest.h = 640;

}

Background::~Background()
{
}

void Background::DrawBackground()
{
	TextureManager::Draw(space, src, dest);
}
