#include "Entity.h"

Entity::~Entity() {
	if (_parent)
		_parent->removeEntity(this);
}

void Entity::setParent(EntityContainer * e) {
	_parent = e;
}

EntityData Entity::getAllData(int gridSize) {
	return EntityData{ getID(), (signed char)position.x / (signed char)gridSize, (signed char)position.y / (signed char)gridSize, getData() };
}

#define ID_BIND(GRID,INDEX,CLASS) if(data->ID == INDEX) { Entity* ent = new CLASS(); ent->loadData(data); return ent; }

#include "SpawnPoint.h"
#include "LevelConnector.h"

Entity* Entity::loadEntityFromData(const EntityData* data, int gridSize) {
	ID_BIND(gridSize, 0, SpawnPoint);
	ID_BIND(gridSize, 1, LevelConnector);


}