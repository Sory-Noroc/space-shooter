#pragma once
#include <SDL.h>

class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	void handleEvents();
	void update() const;
	void render() const;
	void clean() const;

	bool running() const { return isRunning;  }
private:
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;
};
