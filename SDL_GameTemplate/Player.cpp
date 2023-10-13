#include <iostream>
#include "Player.h"
#include "TextureManager.h"

Player::Player(const char* path, SDL_Renderer* renderer): renderer(renderer)
{
   setTex(path);
}

void Player::setTex(const char* path)
{
   texture = TextureManager::LoadTexture(path, renderer);
}

void Player::init()
{
   srcRect.x = srcRect.y = 0;
   srcRect.w = srcRect.h = 32;
   destRect.w = destRect.h = 64;
}

void Player::moveLeft(int step)
{
	destRect.x -= step;
}

void Player::moveRight(int step)
{
	destRect.x += step;
}

void Player::update()
{
	std::cout << "Updating Player";
}


void Player::draw()
{
   TextureManager::Draw(texture, srcRect, destRect, renderer);
}