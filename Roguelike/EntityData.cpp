#include "EntityData.h"

const bool operator==(const EntityData& a, const EntityData& b) {
	return (a.ID == b.ID && a.data == b.data && a.x == b.x && a.y == b.y);
}
