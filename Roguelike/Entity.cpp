#include "Entity.h"

Entity::~Entity() {
	if (_parent)
		_parent->removeEntity(this);
}

void Entity::setParent(EntityContainer * e) {
	_parent = e;
}
