#include <iostream>
#include "Game.h"
#include "Background.h"
#include "TextureManager.h"
#include "Spaceship.h"
#include "Components.h"
#include "Collision.h"
#include "KeyboardController.h"
#include "BulletManagerComponent.h"
#include "GameManager.h"

GameManager manager;
Background* background;
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;


Entity& player(manager.addEntity());

Game::Game() : isRunning(false), window(nullptr)
{
}

Game::~Game()
{
	//delete spaceship;
}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystems initialized" << std::endl;
		auto window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window != nullptr)
		{
			std::cout << "Window created" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (renderer != nullptr)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer created" << std::endl;
		}
		isRunning = true;
	}
	else
	{
		isRunning = false;
	}

	background = new Background(renderer);
	player.addComponent<PositionComponent>(5, stop);
	player.addComponent<SpriteComponent>("assets/ship.png", 200, 5, 2);
	player.addComponent<KeyboardController>();
	player.addComponent<BulletManagerComponent>(1000, 4, -1);
	manager.spawnEnemy(100, 100);
}

void Game::handleEvents()
{
	int x_velocity = 0; // Flag to be set depending on key presses and updated after the loop


	SDL_PollEvent(&event);
	/* Poll for events. SDL_PollEvent() returns 0 when there are no  */
	/* more events on the event queue, our while loop will exit when */
	/* that occurs.
	*/
	switch (event.type)
	{
	case SDL_QUIT: {
		isRunning = false;
		break;
	}
	default:
		break;
	}
}

void Game::update() const
{
	manager.refresh();
	manager.update();
}

void Game::render() const
{
	SDL_RenderClear(renderer);
	// this is where we would add stuff to render
	background->DrawBackground();
	manager.draw();
	SDL_RenderPresent(renderer);
}

void Game::clean() const
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_QUIT;
	std::cout << "Game cleaned" << std::endl;
}