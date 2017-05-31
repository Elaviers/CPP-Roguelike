#pragma once
#include <vector>

struct Tile {
	signed char layer;
	unsigned char id;
	signed char x;
	signed char y;

	static const Tile* pointOverlaps(const std::vector<Tile>& tileData, int tileSize, signed char layer, int x, int y);
	static const Tile* rectOverlaps(const std::vector<Tile>& tileData, int tileSize, signed char layer, int x1, int y1, int x2, int y2);
};
