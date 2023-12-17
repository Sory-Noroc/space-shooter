#pragma once

class entityData {
public:
	const char* path;
	int w;
	int h;
	int scale;
	int spriteCols;
	int spriteRows;
	int spriteDelay;
};

const entityData shipData[2] = { {"assets/ship.png", 16, 24, 5, 5, 2, 200}, {"assets/enemy-big.png", 32, 32, 3, 2, 1, 200} };
const entityData bulletData[2] = { {"assets/laser-bolts.png", 5, 5, 4, 2, 1, 200}, {"assets/laser-bolts.png", 5, 5, 2, 2, 1, 200} };