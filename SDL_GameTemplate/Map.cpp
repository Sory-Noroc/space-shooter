#include "Map.h"
#include "TextureManager.h"
#include "SDL.h"

Map::Map(SDL_Renderer* renderer)
{
	this->renderer = renderer;
	dirt = TextureManager::LoadTexture("assets/dirt.png", renderer);
	grass = TextureManager::LoadTexture("assets/grass.png", renderer);
	water = TextureManager::LoadTexture("assets/water.png", renderer);

	src.x = 0;
	src.y = 0;
	src.w = 32;
	src.h = 32;
	dest.x = 0;
	dest.y = 0;
	dest.w = 32;
	dest.h = 32;

}

Map::~Map()
{

}

void Map::DrawMap()
{
	int type = 0;
	for (int row = 0; row < 20; row++)
	{
		for (int column = 0; column < 25; column++)
		{
			type = map[row][column];

			dest.x = column * 32;
			dest.y = row * 32;
			switch (type)
			{
			case 0:
				{
				TextureManager::Draw(water, src, dest, renderer);
					break;
				}
			case 1:
			{
				TextureManager::Draw(grass, src, dest, renderer);
				break;
			}
			case 2:
			{
				TextureManager::Draw(dirt, src, dest, renderer);
				break;
			}
			default:
				break;
			}
		}
	}
}
