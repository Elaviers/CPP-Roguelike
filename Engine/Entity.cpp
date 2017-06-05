#include "Entity.h"

Entity::Entity() {
	_register = EntityRegistry::getEntityRegister(this);
}

Entity::~Entity() {
}

const unsigned char Entity::getID() const { 
	return _register ? _register->getID() : 255;
}

const std::string Entity::getName() const { 
	return _register ? _register->getName() : "Entity";
}
