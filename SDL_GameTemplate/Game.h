#pragma once
#include <SDL.h>
#include <iostream>
#include <vector>
#include <SDL_ttf.h>
#include "ScoreText.h"

//Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 640;
class ColliderComponent;

class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	void handleEvents();
	void update();
	void render() const;
	void clean() const;
	bool running() const { return isRunning; }
	void finish() { isRunning = false; }
	static std::vector<ColliderComponent*> colliders;
	static std::vector<ColliderComponent*> entitiesHit;
	static SDL_Renderer* renderer;
	static SDL_Event event;
	static void eraseCollider(ColliderComponent* c);

private:
	bool isRunning;
	SDL_Window* window;
	ScoreText* scoreText;
};
