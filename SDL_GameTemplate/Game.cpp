#include "Game.h"
#include <iostream>
#include "Background.h"
#include "Player.h"

Background* background;

Player *player;

const int STEP = 1;

Game::Game(): isRunning(false), window(nullptr), renderer(nullptr)
{
}

Game::~Game()
{
   delete player;
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
		if (window!=nullptr)
		{
			std::cout << "Window created" << std::endl;
		}
 
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (renderer != nullptr)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255,255);
			std::cout << "Renderer created" << std::endl;
		}
		isRunning = true;
	}
	else
	{
		isRunning = false;
	}

	background = new Background(renderer);
   player = new Player ("assets/spaceship.png", renderer);
   player->init();
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
			x_velocity = -STEP;
			break;

		case SDLK_RIGHT:
			x_velocity = STEP;
			break;

		default:
			break;
		}
		break;

	case SDL_KEYUP:
		switch (event.key.keysym.sym) {
		case SDLK_LEFT:
			if (x_velocity < 0) {
				x_velocity = 0;
			}
			break;
		case SDLK_RIGHT:
			if (x_velocity > 0) {
				x_velocity = 0;
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

	if (x_velocity < 0) {
		player->moveLeft(STEP);
	}
	if (x_velocity > 0) {
		player->moveRight(STEP);
	}
}
void Game::update() const
{
	player->update();
}

void Game::render() const
{
	SDL_RenderClear(renderer);
	// this is where we would add stuff to render
	background->DrawBackground();

	player->draw();
	SDL_RenderPresent(renderer);
}

void Game::clean() const
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_QUIT;
	std::cout << "Game cleaned" << std::endl;
}
