#pragma once
#include <SDL.h>
#include <iostream>
#include <vector>

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
	void update() const;
	void render() const;
	void clean() const;
	bool running() const { return isRunning; }
	static std::vector<ColliderComponent*> colliders;
	static std::vector<ColliderComponent*> entitiesHit;
	static SDL_Renderer* renderer;
	static SDL_Event event;

	static void eraseCollider(ColliderComponent* c) {
		colliders.erase(std::remove_if(std::begin(colliders), std::end(colliders),
			[c](ColliderComponent* coll)
			{
				return coll == c;
			}),
			std::end(colliders)
				);
	}

private:
	bool isRunning;
	SDL_Window* window;
};
