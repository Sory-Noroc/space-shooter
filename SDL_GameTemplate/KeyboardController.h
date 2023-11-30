#pragma once

#include "Game.h"
#include "ECS.h"
#include "Components.h"
#include "BulletManagerComponent.h"

class KeyboardController : public Component {
public:
	PositionComponent* transform;

	KeyboardController() = default;

	void init() override
	{
		transform = &entity->getComponent<PositionComponent>();
	}

	void update() override {
		if (Game::event.type == SDL_KEYDOWN) {
			switch (Game::event.key.keysym.sym) {
				case SDLK_UP:
				case SDLK_w:
					transform->velocity.y = -1;
					break;
				case SDLK_LEFT:
				case SDLK_a:
					transform->velocity.x = -1;
					break;
				case SDLK_DOWN:
				case SDLK_s:
					transform->velocity.y = 1;
					break;
				case SDLK_RIGHT:
				case SDLK_d:
					transform->velocity.x = 1;
					break;
				case SDLK_SPACE:
					entity->getComponent<BulletManagerComponent>().makeBullet();
					break;
				default:
					break;
			}
		}

		if (Game::event.type == SDL_KEYUP) {
			switch (Game::event.key.keysym.sym) {
			case SDLK_UP:
			case SDLK_w:
				transform->velocity.y = 0;
				break;
			case SDLK_LEFT:
			case SDLK_a:
				transform->velocity.x = 0;
				break;
			case SDLK_DOWN:
			case SDLK_s:
				transform->velocity.y = 0;
				break;
			case SDLK_RIGHT:
			case SDLK_d:
				transform->velocity.x = 0;
				break;
			case SDLK_SPACE:


				break;
			default:
				break;
			}
		}
	}
};