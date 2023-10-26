#include <iostream>
#include "Game.h"
#include "Background.h"
#include "TextureManager.h"
#include "Spaceship.h"
#include "ECS.h"
#include "Components.h"

Background* background;
Spaceship *spaceship;
Manager manager;

auto& player(manager.addEntity());

const int STEP = 5;

Game::Game() : isRunning(false), window(nullptr), renderer(nullptr)
{
}

Game::~Game()
{
	delete spaceship;
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
	spaceship = new Spaceship("assets/ship.png", renderer);
	spaceship->init();

	player.addComponent<PositionComponent>();
	player.getComponent<PositionComponent>("assets/spaceship.png");
}

void Game::handleEvents()
{
	SDL_Event event;
	int x_velocity = 0; // Flag to be set depending on key presses and updated after the loop


	SDL_PollEvent(&event);
	/* Poll for events. SDL_PollEvent() returns 0 when there are no  */
	/* more events on the event queue, our while loop will exit when */
	/* that occurs.
	*/
	switch (event.type)
	{
	case SDL_KEYDOWN:

		switch (event.key.keysym.sym)
		{
		case SDLK_LEFT:
			if (event.key.repeat == 0) {
				left = 1;
			}
			break;

		case SDLK_RIGHT:
			if (event.key.repeat == 0) {
				right = 1;
			}
			break;

		default:
			break;
		}
		break;

	case SDL_KEYUP:
		switch (event.key.keysym.sym) {
		case SDLK_LEFT:
			if (event.key.repeat == 0) {
				left = 0;
			}
			break;
		case SDLK_RIGHT:
			if (event.key.repeat == 0) {
				right = 0;
			}
			break;
		default:
			break;
		}
		break;

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
	if (left == 1) {
		spaceship->moveLeft(STEP);
	}
	else if (right == 1) {
		spaceship->moveRight(STEP);
	}
	spaceship->update();
	manager.update();
}

void Game::render() const
{
	SDL_RenderClear(renderer);
	// this is where we would add stuff to render
	background->DrawBackground();

	spaceship->draw();
	SDL_RenderPresent(renderer);
}

void Game::clean() const
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_QUIT;
	std::cout << "Game cleaned" << std::endl;
}