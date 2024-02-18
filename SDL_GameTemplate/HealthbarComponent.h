#pragma once
#include "ECS.h"
#include "Components.h"
#include "TextureManager.h"

constexpr SDL_Color gray = { 90, 80, 60, 200 };
constexpr SDL_Color red = { 152, 5, 5, 255 };
constexpr int h = 10;  // Height of the healthbar

class HealthbarComponent : public Component {
	int health = 0, maxHealth = 0;
	int w = 0;
	PositionComponent* pos = nullptr;
	SDL_Rect healthR, otherR, srcHealth, srcOther;
	SDL_Texture* healthT = nullptr, *otherT = nullptr;
	SDL_Surface* healthS = nullptr, *otherS = nullptr;

public:
	void init() override {
		maxHealth = entity->health;
		health = maxHealth;
		if (entity->hasComponent<PositionComponent>()) {
			pos = &entity->getComponent<PositionComponent>();
		}
		w = pos->width * pos->scale;

		healthS = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);
		if (healthS == nullptr) {
			printf("Error creating surface with code %s\n", SDL_GetError());
		}
		else {
			SDL_FillRect(healthS, nullptr, SDL_MapRGB(healthS->format, red.r, red.g, red.b));
		}

		otherS = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);
		if (otherS == nullptr) {
			printf("Error creating surface with code %s\n", SDL_GetError());
		}
		else {
			SDL_FillRect(otherS, nullptr, SDL_MapRGBA(otherS->format, gray.r, gray.g, gray.b, gray.a));
		}

		healthT = TextureManager::LoadTexture(healthS);
		otherT = TextureManager::LoadTexture(otherS);

		srcHealth.x = 0;
		srcHealth.y = 0;
		srcOther.x = 0;
		srcOther.x = 0;
		updateRects(w);
	}

	void update() override {
		const int healthWidth = entity->health * w / maxHealth;
		healthR.x = static_cast<int>(pos->position.x);
		healthR.y = static_cast<int>(pos->position.y + pos->height * pos->scale + h);
		otherR.x = static_cast<int>(pos->position.x) + healthWidth;
		otherR.y = static_cast<int>(pos->position.y + pos->height * pos->scale + h);

		if (health != entity->health) {
			// Only update the health bar if the health changed
			updateRects(healthWidth);
		}
	}

	void updateRects(const int healthWidth) {
		const int otherWidth = w - healthWidth;
		health = entity->health;

		srcHealth.w = healthWidth;
		srcHealth.h = h;
		srcOther.w = otherWidth;
		srcOther.h = h;

		healthR.w = healthWidth;
		healthR.h = h;
		otherR.w = otherWidth;
		otherR.h = h;
	}

	void draw() override {
		TextureManager::Draw(healthT, &srcHealth, &healthR);
		TextureManager::Draw(otherT, &srcOther, &otherR);
	}

	~HealthbarComponent() override {
		SDL_FreeSurface(healthS);
		SDL_FreeSurface(otherS);
		SDL_DestroyTexture(healthT);
		SDL_DestroyTexture(otherT);
	}
};