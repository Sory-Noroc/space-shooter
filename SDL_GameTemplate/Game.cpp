#include "Game.h"
#include "Background.h"
#include "Components.h"
#include "GameManager.h"
#include "ECS.h"

char* scoreString = const_cast<char*>("Score: ");
GameManager manager;
Background* background;
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

std::vector<ColliderComponent*> Game::colliders;
std::vector<ColliderComponent*> Game::entitiesHit;

auto& player(manager.addEntity());

Game::Game() : isRunning(false), window(nullptr)
{
	scoreText = nullptr;
}

Game::~Game() = default;

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

	if (TTF_Init() == -1) {
		exit(-2004);
	}

	background = new Background(renderer);
	scoreText = new ScoreText(scoreString, SCREEN_HEIGHT);
	manager.initPlayer(player);
	manager.spawnEnemies(50,1);
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
	scoreText->update(manager.score);
}

void Game::update()
{
	static int i = 1;
	for (auto& coll1 : colliders) {
		for (auto& coll2 : colliders) {
			if (coll1 != coll2 && coll1->is_colliding(*coll2) && !isIn(entitiesHit, coll1) && !isIn(entitiesHit, coll2)) {
				entitiesHit.push_back(coll1);
				entitiesHit.push_back(coll2);

				coll1->entity->wasHit();
				coll2->entity->wasHit();

				if (coll1->tag == enemy) {
					manager.enemyHit(coll1->entity);
				}
				else if (coll2->tag == enemy) {
					manager.enemyHit(coll2->entity);
				}

				manager.manageAnimation(coll1, coll2);
			}
		}
	}

	if (player.health <= 0) {
		finish();
	}

	for (const auto e : entitiesHit) {
		if (e->entity->health == 0) {
			eraseCollider(e);
		}
	}
	entitiesHit.clear();

	if (manager.enemyCount <= 0)
	{
		if (manager.enemyWave % 4 == 0)
		{
			++i;
			manager.enemyCount = 0;
			manager.enemyWave = 1;
		}
		if (i <= 3)
		{
			manager.spawnEnemies(50, i);
		} else
		{
			i = 1;
		}
	}

	manager.refresh();
	manager.update();
}

void Game::eraseCollider(ColliderComponent* c) {
	colliders.erase(std::remove_if(std::begin(colliders), std::end(colliders),
		[c](const ColliderComponent* coll)
		{
			return coll == c;
		}),
		std::end(colliders)
			);
}

void Game::render() const
{
	SDL_RenderClear(renderer);
	// this is where we would add stuff to render
	background->DrawBackground();
	scoreText->draw();
	manager.draw();
	SDL_RenderPresent(renderer);
}

void Game::clean() const
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_QUIT;
	std::cout << "Game cleaned\n";
}

