#pragma once
#include "ECS.h"
#include "PositionComponent.h"
#include "BulletManagerComponent.h"

class GameManager : public Manager {
public:
	void spawnEnemy(float x, float y) {
		Entity* e = &addEntity();
		e->addComponent<PositionComponent>(x, y, 32, 32).setScale(3);
		e->addComponent<SpriteComponent>("assets/enemy-big.png", 200, 2, 1);
		e->addComponent<BulletManagerComponent>(1000, 3, 1).activate(); // Activate continuous shooting
	}
};