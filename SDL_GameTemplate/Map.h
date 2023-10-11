#pragma once
#include <SDL_image.h>

class Map
{
public:
	Map(SDL_Renderer* renderer);
	~Map();

	void LoadMap(int arr[20][25]);
	void DrawMap();

private:
	SDL_Renderer* renderer;
	SDL_Rect src, dest;
	SDL_Texture* dirt;
	SDL_Texture* grass;
	SDL_Texture* water;

	int map[20][25];
};