#include "Entity.h"

Entity::~Entity() {
	if (_parent)
		_parent->removeEntity(this);
}

void Entity::setParent(EntityContainer * e) {
	_parent = e;
}

#define ID_BIND(PTR,INDEX,CLASS) if(ID == INDEX) {PTR = new CLASS(); return PTR;}

#include "SpawnPoint.h"
#include "LevelConnector.h"

Entity* Entity::createClassForID(unsigned char ID) {
	Entity* ent;
	ID_BIND(ent, 0, SpawnPoint);
	ID_BIND(ent, 1, LevelConnector);

	//Only get here if not a bound ID
	ent = new Entity();
	return ent;
}