#include <iostream>
#include "Game.h"
#include "Spaceship.h"
#include "TextureManager.h"

Spaceship::Spaceship(const char* path, SDL_Renderer* renderer) : renderer(renderer)
{
	setTex(path);
}

void Spaceship::setTex(const char* path)
{
	texture = TextureManager::LoadTexture(path);
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
	if (destRect.x > 0)
	{
		destRect.x -= step;
	}
}

void Spaceship::moveRight(int step)
{
	if (destRect.x < SCREEN_WIDTH - destRect.w)
	{
		destRect.x += step;
	}
}

void Spaceship::update()
{
	destRect.x++;
	destRect.y++;
	/*
	if (left == 1) {
		moveLeft(STEP);
	}
	else if (right == 1) {
		moveRight(STEP);
	*/
}

void Spaceship::draw()
{
	TextureManager::Draw(texture, srcRect, destRect);
}

