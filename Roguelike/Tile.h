#pragma once
#include <Engine/Vector2.h>

struct Tile {
	int layer;
	unsigned char ID;
	Vector2 position;
};

bool operator==(const Tile& a, const Tile& b);
