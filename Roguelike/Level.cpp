#include "Level.h"

#include "FileManager.h"

#include <algorithm>
#include <Engine/IOManager.h>
#include <Engine/ResourceManager.h>
#include <Engine/SpriteRenderer.h>

Level::Level()
{
}


Level::~Level()
{
}

void Level::addTileData(const TileData& tile) {
	if (tile.x > 123 || tile.x < -124 || tile.y > 123 || tile.y < -124)return;

	for (auto it = _tileData.begin(); it != _tileData.end(); it++) //Check for existing tile
		if (it->x == tile.x && it->y == tile.y && it->layer == tile.layer)
			if (it->id != tile.id) {
				_tileData.erase(it);
				return;
			}
			else return;

			auto it = _tileData.begin();
			for (; it != _tileData.end(); it++) //For every tile
				if (tile.layer == it->layer) { //If layer found
					for (; it != _tileData.end() && it->layer == tile.layer; it++) //For each tile in layer
						if (tile.id == it->id) { //If ID found
							for (; it != _tileData.end() && it->layer == tile.layer && it->id == tile.id; it++) //For each tile in ID
								if (tile.x > it->x || (tile.x == it->x && tile.y > it->y)) //If X is over or is on X and Y is over
									break; //Break if X is larger or Y is larger and X is equal
							break; //break after finding ID
						}
					break; //break after finding Layer
				}

			_tileData.insert(it, tile);
}

void Level::removeTileData(const TileData& tile) {
	for (auto it = _tileData.begin(); it != _tileData.end(); it++)
		if (it->layer == tile.layer && it->x == tile.x && it->y == tile.y) {
			_tileData.erase(it);
			return;
		}
}

void Level::addEntityData(const EntityData& data) {
	if (data.x > 123 || data.x < -124 || data.y > 123 || data.y < -124)return;

	for (auto it = _entData.begin(); it != _entData.end(); it++)
		if (data.x == it->x && data.y == it->y)
			if (data.ID != it->ID) {
				_entData.erase(it);
				return;
			}
			else return;

			auto it = _entData.begin();
			for (; it < _entData.end(); it++)
				if (data.ID == it->ID) {
					for (; it != _entData.end() && it->ID == data.ID; it++)
						if (data.x > it->x || (data.x == it->x && data.y > it->y))
							break;
					break;
				}

			_entData.insert(it, data);
}

void Level::removeEntityData(const EntityData& data) {
	for (auto it = _entData.begin(); it != _entData.end(); it++)
		if (it->x == data.x && it->y == data.y) {
			_entData.erase(it);
			return;
		}
}

bool Level::load(const char* path) {
	FileManager::readLevelFile(path, _tileData, _entData);

	return true;
}

bool Level::save(const char* path) {
	FileManager::writeLevelFile(_tileData, _entData, path);

	return true;
}
