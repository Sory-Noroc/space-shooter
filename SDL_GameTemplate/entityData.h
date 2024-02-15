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
	int health;
};

const entityData shipData[4] = { 
	{"assets/ship.png", 16, 24, 5, 5, 2, 200, 3}, 
	{"assets/enemy-small.png", 16, 16, 3, 2, 1, 200, 1},
	{"assets/enemy-medium.png", 32, 16, 3, 2, 1, 200, 2}, 
	{"assets/enemy-big.png", 32, 32, 4, 2, 1, 200, 3} 
};
const entityData bulletData[2] = { 
	{"assets/laser-bolts.png", 5, 5, 4, 2, 1, 200, 1}, 
	{"assets/laser-bolts.png", 5, 5, 2, 2, 1, 200, 1} 
};
const entityData explosionData[1] = { 
	{"assets/explosion.png", 16, 16, 3, 5, 1, 200, 1} 
};