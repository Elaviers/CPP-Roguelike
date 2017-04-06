#include "Tile.h"

bool operator==(const Tile& a, const Tile& b) {
	return (a.layer == b.layer && a.ID == b.ID && a.position == b.position);
}
