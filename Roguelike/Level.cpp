#include "Level.h"

#include "Entity.h"
#include "FileManager.h"

#include <Engine/IOManager.h>
#include <Engine/ResourceManager.h>
#include <Engine/SpriteRenderer.h>

Level::Level() : _tileSize(64)
{
}


Level::~Level()
{
}

void Level::addTile(const Tile& tile) {
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

void Level::removeTile(signed char layer, signed char x, signed char y) {
	for (auto it = _tiles.begin(); it != _tiles.end(); it++)
		if (it->layer == layer && it->x == x && it->y == y) {
			_tiles.erase(it);
			return;
		}
}

void Level::addEntity(Entity* ent) {
	//if (ent->position.x > 123 || ent->position.x < -124 || ent->position.y > 123 || ent->position.y < -124)return;

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
	std::printf("Created entity (id %d, name %s)\n", ent->getID(), ent->getName().c_str());
}

void Level::removeEntity(const Vector2f& position) {
	for (auto it = _entities.begin(); it != _entities.end(); it++)
		if ((*it)->position == position) {
			_entities.erase(it);
			return;
		}
}

bool Level::load(const char* path) {
	FileManager::readLevelFile(path, _tiles, _entities);

	return true;
}

bool Level::save(const char* path) const {
	FileManager::writeLevelFile(_tiles, _entities, path);

	return true;
}

void Level::drawTiles(signed char maxlayer, bool resetiterator, const Rect_i& cameradimensions, const Texture& texture) const {
	static int _tileIndex = 0;

	if (resetiterator)
		_tileIndex = 0;

	for (auto it = _tiles.begin() + _tileIndex; it != _tiles.end() && it->layer <= maxlayer; it++, _tileIndex++) {
		if (it->x * _tileSize < cameradimensions.max.x && it->y * _tileSize < cameradimensions.max.y && it->x * _tileSize + _tileSize > cameradimensions.min.x && it->y * _tileSize + _tileSize > cameradimensions.min.y)
			SpriteRenderer::drawSprite(texture, (float)(it->x * _tileSize), (float)(it->y * _tileSize), (float)_tileSize, (float)_tileSize, 0.f, it->id);
	}
}

void Level::drawEntities(Shader& shader) const {
	for (auto it = _entities.begin(); it != _entities.end(); it++)
		(*it)->render(shader);
}

void Level::updateEntities(float deltatime) const {
	for (auto it = _entities.begin(); it != _entities.end(); it++)
		(*it)->update(deltatime);
}
