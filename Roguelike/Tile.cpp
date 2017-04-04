#include "Tile.h"

bool operator<(const Tile& a, const Tile& b) {
	return (a.layer < b.layer || a.TileID < b.TileID || a.x < b.x || a.y < b.y);
}
