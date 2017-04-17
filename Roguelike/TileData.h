#pragma once
#include <vector>

struct TileData {
	signed char layer;
	unsigned char id;
	signed char x;
	signed char y;

	static const TileData* pointOverlaps(const std::vector<TileData>& tileData, int tileSize, signed char layer, int x, int y);
	static const TileData* rectOverlaps(const std::vector<TileData>& tileData, int tileSize, signed char layer, int x1, int y1, int x2, int y2);
};
