#include "EntityContainer.h"

#include "Entity.h"

#include <algorithm>

EntityContainer::EntityContainer()
{
}


EntityContainer::~EntityContainer() {
	while (_entities.size() > 0)
		delete _entities.back();
}

void EntityContainer::addEntity(Entity* entity) {
	entity->setParent(this);

	if (_updating)
		_add.push_back(entity);
	else
		_entities.push_back(entity);
}

void EntityContainer::removeEntity(Entity* entity) {
	if (_updating)
		_delete.push_back(entity);
	else
		_entities.erase(std::remove(_entities.begin(), _entities.end(), entity), _entities.end());
}

void EntityContainer::update(float deltaTime) {
	_updating = true;
	for (auto it = _entities.begin(); it != _entities.end(); it++)
		(*it)->update(deltaTime);
	_updating = false;

	while (_add.size() > 0) {
		_entities.push_back(_add.back());
		_add.pop_back();
	}

	while (_delete.size() > 0) {
		_entities.erase(std::remove(_entities.begin(), _entities.end(), _delete.back()), _entities.end());
		_delete.pop_back();
	}
}

void EntityContainer::render(Shader& shader) {
	for (auto it = _entities.begin(); it != _entities.end(); it++)
		(*it)->render(shader);
}
