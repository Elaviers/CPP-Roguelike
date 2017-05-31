#include "Tile.h"

const Tile* Tile::pointOverlaps(const std::vector<Tile>& tileData, int tileSize, signed char layer, int x, int y) {
	for (auto t = tileData.begin(); t != tileData.end() && t->layer >= layer; t++)
		if (t->layer == layer && x > t->x * tileSize && y > t->y * tileSize && x < t->x * tileSize + tileSize && y < t->y * tileSize + tileSize)
			return &(*t);
	return NULL;
}

const Tile* Tile::rectOverlaps(const std::vector<Tile>& tileData, int tileSize, signed char layer, int x1, int y1, int x2, int y2) {
	for (auto t = tileData.begin(); t != tileData.end() && t->layer >= layer; t++)
		if (t->layer == layer && !(x2 <= t->x * tileSize || y2 <= t->y * tileSize || x1 >= t->x * tileSize + tileSize || y1 >= t->y * tileSize + tileSize))
			return &(*t);
	return NULL;
}
