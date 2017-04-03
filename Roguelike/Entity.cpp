#include "Entity.h"

bool operator<(const EntityData& a, const EntityData& b) {
	return (a.ID < b.ID || a.position.x < b.position.x || a.position.y < b.position.y);
}

Entity::Entity(unsigned char id, Vector2f p) : ID(id)
{
	this->position = p;
}


Entity::~Entity()
{
}
