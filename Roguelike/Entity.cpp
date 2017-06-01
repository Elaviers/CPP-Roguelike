#include "Entity.h"
#include "EntityRegistry.h"

Entity::Entity() {
}

Entity::~Entity() {
	if (_parent)
		_parent->removeEntity(this);
}

void Entity::setParent(EntityContainer * e) {
	_parent = e;
}

const unsigned char Entity::getID() const { return EntityRegistry::getEntityRegister(this)->getID(); }
const std::string Entity::getName() const { return EntityRegistry::getEntityRegister(this)->getName(); }
