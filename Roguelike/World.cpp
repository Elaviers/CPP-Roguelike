#include "World.h"

#include "FileManager.h"

#include <algorithm>
#include <Engine/Entity.h>
#include <Engine/IOManager.h>
#include <Engine/ResourceManager.h>
#include <Engine/SpriteRenderer.h>

std::vector<Tile> World::_tiles;
std::vector<Entity*> World::_entities;
int World::_tileSize = 64;

std::vector<Entity*>::iterator World::_iterator;

void World::addTile(const Tile& tile) {
	if (tile.x > 123 || tile.x < -124 || tile.y > 123 || tile.y < -124)return;

	for (auto it = _tiles.begin(); it != _tiles.end(); it++) { //Check for existing tile
		if (it->x == tile.x && it->y == tile.y && it->layer == tile.layer) {
			if (it->id == tile.id) return;
			else {
				_tiles.erase(it);
				break;
			}
		}
	}

	auto it = _tiles.begin();
	for (; it != _tiles.end(); it++) //For every tile
		if (tile.layer == it->layer) { //If layer found
			for (; it != _tiles.end() && it->layer == tile.layer; it++) //For each tile in layer
				if (tile.id == it->id) { //If ID found
					for (; it != _tiles.end() && it->layer == tile.layer && it->id == tile.id; it++) //For each tile in ID
						if (tile.x > it->x || (tile.x == it->x && tile.y > it->y)) //If X is over or is on X and Y is over
							break; //Break if X is larger or Y is larger and X is equal
					break; //break after finding ID
				}
			break; //break after finding Layer
		}
		else if (tile.layer < it->layer) break;

	_tiles.insert(it, tile);
}

void World::removeTile(signed char layer, signed char x, signed char y) {
	for (auto it = _tiles.begin(); it != _tiles.end(); it++)
		if (it->layer == layer && it->x == x && it->y == y) {
			_tiles.erase(it);
			return;
		}
}

void World::addEntity(Entity* ent, bool sort) {
	//if (ent->position.x > 123 || ent->position.x < -124 || ent->position.y > 123 || ent->position.y < -124)return;

	if (sort) {
		for (auto it = _entities.begin(); it != _entities.end(); it++) {
			if (ent->position == (*it)->position) {
				if (ent->getID() == (*it)->getID()) return;
				else {
					_entities.erase(it);
					break;
				}
			}
		}

		auto it = _entities.begin();
		for (; it != _entities.end(); it++)
			if (ent->getID() == (*it)->getID()) {
				for (; it != _entities.end() && (*it)->getID() == ent->getID(); it++)
					if (ent->position.x > (*it)->position.x || (ent->position == (*it)->position))
						break;
				break;
			}

		_entities.insert(it, ent);
	}
	else { _iterator = _entities.insert(_iterator, ent) + 2; }
}

void World::removeEntity(Entity* ent) {
	_entities.erase(std::remove(_entities.begin(),_entities.end(), ent), _entities.end());
}

void World::removeEntityAtPosition(const Vector2f& position) {
	for (auto it = _entities.begin(); it != _entities.end(); it++)
		if ((*it)->position == position) {
			_entities.erase(it);
			return;
		}
}

bool World::load(const char* path) {
	bool success = FileManager::readLevelFile(path, _tiles, _entities);

	_iterator = _entities.begin();

	return success;
}

bool World::save(const char* path) {
	return FileManager::writeLevelFile(_tiles, _entities, path);
}

void World::drawTiles(signed char maxlayer, bool resetiterator, const Rect_i& cameradimensions, const Texture& texture) {
	static int _tileIndex = 0;

	if (resetiterator)
		_tileIndex = 0;

	for (auto it = _tiles.begin() + _tileIndex; it != _tiles.end() && it->layer <= maxlayer; it++, _tileIndex++) {
		if (it->x * _tileSize < cameradimensions.max.x && it->y * _tileSize < cameradimensions.max.y && it->x * _tileSize + _tileSize > cameradimensions.min.x && it->y * _tileSize + _tileSize > cameradimensions.min.y)
			SpriteRenderer::drawSprite(texture, (float)(it->x * _tileSize), (float)(it->y * _tileSize), (float)_tileSize, (float)_tileSize, 0.f, it->id);
	}
}

void World::drawEntities(Shader& shader) {
	for (auto it = _entities.begin(); it != _entities.end(); it++)
		(*it)->render(shader);
}

void World::updateEntities(float deltatime) {
	_iterator = _entities.begin();

 	for (; _iterator < _entities.end(); _iterator++) //Using < in case reallocation shrinks vector
		(*_iterator)->update(deltatime);
}
