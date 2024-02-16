#pragma once
#include "ECS.h"
#include "Components.h"
#include "entityData.h"
#include "Animation.h"
#include "HealthbarComponent.h"

class GameManager : public Manager {
	std::vector<Entity*> entitiesToAdd;

public:
	int enemyWave = 1;
	int enemyCount = 0;
	int score = 0;

	void initPlayer(Entity& player) {
		int shipIndex = 0;
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
		e->addComponent<PositionComponent>(x, y, enemy.w, enemy.h).setScale(enemy.scale);
		e->addComponent<SpriteComponent>(enemy.path, enemy.spriteDelay, enemy.spriteCols, enemy.spriteRows);
		e->addComponent<BulletManagerComponent>(1000, bullet.scale, 1.f, 1).activate(); // Activate continuous shooting
		e->addComponent<MovementComponent>();
		e->addComponent<ColliderComponent>(tag::enemy);
		e->addComponent<HealthbarComponent>();
	}

	void spawnEnemies(int y, int enemyIndex, int bulletIndex = 1) {
		int x, enemyWidth = shipData[enemyIndex].w * shipData[enemyIndex].scale;
		int distance = (SCREEN_WIDTH - enemyWave * enemyWidth) / (enemyWave + 1);
		for (int i = 0; i < enemyWave; i++) {
			x = distance * (i + 1) + enemyWidth * i;
			spawnEnemy(x, y, enemyIndex, bulletIndex);
		}
		enemyCount += enemyWave;
		enemyWave++;
	}

	void enemyHit(Entity* enemy) {
		if (enemy->health == 0) {
			enemyCount--;
			score += static_cast<int>(pow(enemy->health, 2));
		}
	}

	void update() {
		Manager::update();
		// Add entities
		for (auto& e : entitiesToAdd) {
			addEntity(e);
		}
		entitiesToAdd.clear();
	}

	void addEntityToQueue(Entity* e) {
		entitiesToAdd.emplace_back(e);
	}

	void makeAnimation(int x, int y, int animationIndex=0) {
		Entity* e = new Entity(*this);
		addEntityToQueue(e);
		e->addComponent<Animation>(x, y, explosionData[animationIndex]);
	}
};