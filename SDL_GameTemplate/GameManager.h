#pragma once
#include "ECS.h"
#include "Components.h"
#include "entityData.h"
#include "Animation.h"

class GameManager : public Manager {
	std::vector<Entity*> entitiesToAdd;

public:
	int enemyWave = 1;
	int enemyCount = 0;
	void spawnEnemy(float x, float y, int enemyIndex, int bulletIndex) {
		entityData enemy = shipData[enemyIndex];
		entityData bullet = bulletData[bulletIndex];
		Entity* e = new Entity(*this);
		addEntityToQueue(e);

		e->addComponent<PositionComponent>(x, y, enemy.w, enemy.h).setScale(enemy.scale);
		e->addComponent<SpriteComponent>(enemy.path, enemy.spriteDelay, enemy.spriteCols, enemy.spriteRows);
		e->addComponent<BulletManagerComponent>(1000, bullet.scale, 1.f, 1).activate(); // Activate continuous shooting
		e->addComponent<MovementComponent>();
		e->addComponent<ColliderComponent>(tag::enemy);
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