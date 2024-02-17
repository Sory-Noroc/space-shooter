#pragma once
#include "ECS.h"
#include "Components.h"
#include "entityData.h"
#include "Animation.h"
#include "HealthbarComponent.h"
#include "KeyboardController.h"

class GameManager : public Manager {
	std::vector<Entity*> entitiesToAdd;

public:
	int enemyWave = 1;
	int enemyCount = 0;
	int score = 0;

	static void initPlayer(Entity& player) {
		constexpr int shipIndex = 0;
		entityData ship = shipData[shipIndex];
		entityData shipBullet = bulletData[shipIndex];
		player.health = ship.health;
		player.addComponent<PositionComponent>(200.0f, 200.0f, ship.w, ship.h, stop).setScale(ship.scale)->setSpeed(3);
		player.addComponent<KeyboardController>();
		player.addComponent<ColliderComponent>(champ);
		player.addComponent<SpriteComponent>(ship.path, ship.spriteDelay, ship.spriteCols, ship.spriteRows);
		player.addComponent<BulletManagerComponent>(1000, shipBullet.scale, -1.f, 0);
		player.addComponent<HealthbarComponent>();
	}

	void spawnEnemy(int x, int y, int enemyIndex, int bulletIndex) {
		entityData enemy = shipData[enemyIndex];
		entityData bullet = bulletData[bulletIndex];
		Entity* e = new Entity(*this);
		addEntityToQueue(e);

		e->health = enemy.health;
		e->maxHealth = e->health;
		e->addComponent<PositionComponent>(x, y, enemy.w, enemy.h).setScale(enemy.scale);
		e->addComponent<SpriteComponent>(enemy.path, enemy.spriteDelay, enemy.spriteCols, enemy.spriteRows);
		e->addComponent<BulletManagerComponent>(1000, bullet.scale, 1.f, 1).activate(); // Activate continuous shooting
		e->addComponent<MovementComponent>();
		e->addComponent<ColliderComponent>(tag::enemy);
		e->addComponent<HealthbarComponent>();
	}

	void spawnEnemies(const int y, const int enemyIndex, const int bulletIndex = 1) {
		int x;
		const int enemyWidth = shipData[enemyIndex].w * shipData[enemyIndex].scale;
		const int distance = (SCREEN_WIDTH - enemyWave * enemyWidth) / (enemyWave + 1);
		for (int i = 0; i < enemyWave; i++) {
			x = distance * (i + 1) + enemyWidth * i;
			spawnEnemy(x, y, enemyIndex, bulletIndex);
		}
		enemyCount += enemyWave;
		enemyWave++;
	}

	void enemyHit(const Entity* enemy) {
		if (enemy->health == 0) {
			enemyCount--;
			score += static_cast<int>(pow(enemy->maxHealth, 2));
		}
	}

	void update() override
	{
		Manager::update();
		// Add entities
		for (const auto e : entitiesToAdd)
		{
			addEntity(e);
		}
		entitiesToAdd.clear();
	}

	void addEntityToQueue(Entity* e) override {
		entitiesToAdd.emplace_back(e);
	}

	void manageAnimation(const ColliderComponent* coll1, const ColliderComponent* coll2) {

		if (coll1->tag == champBullet || coll1->tag == enemyBullet)
		{
			const Vector2D pos = coll2->entity->getComponent<PositionComponent>().position;
			makeAnimation(static_cast<int>(pos.x), static_cast<int>(pos.y), coll2->entity);
		}
		else {
			const auto pos = coll1->entity->getComponent<PositionComponent>().position;
			makeAnimation(static_cast<int>(pos.x), static_cast<int>(pos.y), coll1->entity);
		}
	}

	void makeAnimation(int x, int y, const Entity* entityHit, const int animationIndex=0) {
		/*
		Docs description
		*/
		auto* e = new Entity(*this);
		int w, h;
		PositionComponent pos = entityHit->getComponent<PositionComponent>();
		w = pos.width * pos.scale;
		h = pos.height * pos.scale;
		
		// Getting the max value to make a square explosion not a distorted one
		if (w > h) {
			h = w;
		}
		else {
			w = h;
		}
		addEntityToQueue(e);
		e->addComponent<Animation>(x, y, w, h, explosionData[animationIndex]);
	}
};