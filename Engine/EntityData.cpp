#include "EntityData.h"

bool operator==(const EntityData& a, const EntityData& b) {
	return (a.ID == b.ID && a.data == b.data && a.position.x == b.position.x && a.position.y == b.position.y);
}


bool operator<(const EntityData& a, const EntityData& b) {
	return (a.ID < b.ID || a.position.x < b.position.x || a.position.y < b.position.y);
}
