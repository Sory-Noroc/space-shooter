#include "Game.h"
#include "Background.h"
#include "TextureManager.h"
#include "Components.h"
#include "Collision.h"
#include "KeyboardController.h"
#include "BulletManagerComponent.h"
#include "GameManager.h"
#include "entityData.h"
#include "ECS.h"

GameManager manager;
Background* background;
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

std::vector<ColliderComponent*> Game::colliders;
std::vector<ColliderComponent*> Game::entitiesHit;

auto& player(manager.addEntity());

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

	SDL_Color white = { 255, 255, 255, 255 };
	//TTF_RenderText_Solid(TTF_OpenFont("assets/Terminal.ttf", 28), "Space Shooter", white);

	int shipIndex = 0;
	background = new Background(renderer);
	entityData ship = shipData[shipIndex];
	entityData shipBullet = bulletData[shipIndex];
	player.addComponent<PositionComponent>(200.0f, 200.0f, ship.w, ship.h, stop).setScale(ship.scale)->setSpeed(3);
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>(champ);
	player.addComponent<SpriteComponent>(ship.path, ship.spriteDelay, ship.spriteCols, ship.spriteRows);
	player.addComponent<BulletManagerComponent>(1000, shipBullet.scale, -1.f, 0);
	manager.spawnEnemies(50);
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
	for (auto& coll1 : colliders) {
		for (auto& coll2 : colliders) {
			if (coll1 != coll2 && coll1->is_colliding(*coll2)) {
				entitiesHit.push_back(coll1);
				entitiesHit.push_back(coll2);

				if (coll1->tag == enemy) {
					manager.enemyCount--;
				}

				coll1->entity->destroy();
				coll2->entity->destroy();
			}
		}
	}

	for (auto& e : entitiesHit) {
		eraseCollider(e);
	}
	entitiesHit.clear();

	if (manager.enemyCount <= 0) {
		manager.spawnEnemies(50);
	}
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

