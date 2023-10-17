#include <iostream>
#include "Spaceship.h"
#include "TextureManager.h"

Spaceship::Spaceship(const char* path, SDL_Renderer* renderer): renderer(renderer)
{
   setTex(path);
}

void Spaceship::setTex(const char* path)
{
   texture = TextureManager::LoadTexture(path, renderer);
}

void Spaceship::init()
{
   srcRect.x = srcRect.y = 0;
   destRect.x = 350;
   destRect.y = 500;
   srcRect.w = srcRect.h = 50;
   destRect.w = destRect.h = 80;
}

void Spaceship::moveLeft(int step)
{
	destRect.x -= step;
}

void Spaceship::moveRight(int step)
{
	destRect.x += step;
}

void Spaceship::update()
{
	std::cout << "Updating Spaceship";
}


void Spaceship::draw()
{
   TextureManager::Draw(texture, srcRect, destRect, renderer);
}