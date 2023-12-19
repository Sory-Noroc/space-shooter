#pragma once
#include "ECS.h"
#include "PositionComponent.h"
#include "BulletManagerComponent.h"
#include "entityData.h"

class GameManager : public Manager {
public:
	void spawnEnemy(float x, float y, int enemyIndex, int bulletIndex) {
		entityData enemy = shipData[enemyIndex];
		entityData bullet = bulletData[bulletIndex];
		Entity* e = &addEntity();
		e->addComponent<PositionComponent>(x, y, enemy.w, enemy.h).setScale(enemy.scale);
		e->addComponent<SpriteComponent>(enemy.path, enemy.spriteDelay, enemy.spriteCols, enemy.spriteRows);
		e->addComponent<BulletManagerComponent>(1000, bullet.scale, 1.f, 1).activate(); // Activate continuous shooting
		e->addComponent<ColliderComponent>(tag::enemy);
	}
};