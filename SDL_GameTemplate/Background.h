#pragma once
#include <SDL_image.h>

class Background
{
public:
	Background(SDL_Renderer* renderer);
	~Background();
	void DrawBackground();

private:
	SDL_Renderer* renderer;
	SDL_Rect src, dest;
	SDL_Texture* space;
};