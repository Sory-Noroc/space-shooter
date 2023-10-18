//Using SDL and standard IO
#include "Game.h"
#include <SDL.h>

int main(int argc, char* args[])
{
	const int fps = 120;
	// max time between frames
	const int frameDelay = 1000 / fps;
	Game *game = new Game();
	bool fullscreen = false;

	game->init("Space Shooter", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, fullscreen);

	while (game->running())
	{
		Uint32 frameStart = SDL_GetTicks();
		game->handleEvents();
		game->update();
		game->render();
		const int frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game->clean();
	delete game;
	return 0;
}