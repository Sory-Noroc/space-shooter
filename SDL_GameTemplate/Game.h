#pragma once
#include <SDL.h>

//Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 640;

class Game
{
public:
	Game();
	~Game();
	int left, right;

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
