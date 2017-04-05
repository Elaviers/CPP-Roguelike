#include "Level.h"

#include "FileManager.h"

#include <algorithm>
#include <Engine/ResourceManager.h>
#include <Engine/SpriteRenderer.h>

Level::Level()
{
}


Level::~Level()
{
}

Tile* Level::getData() {
	return _tiles.data();
}

const float tileSize = 64;

Vector2 Level::getSpawnPoint() {
	std::vector<unsigned int> spawnpoints;

	for (int i = 0; i < _entData.size(); i++) {
		if (_entData[i].ID == 0)
			spawnpoints.push_back(i);
	}

	if (spawnpoints.size() > 0)
		return _entData[spawnpoints[rand() % spawnpoints.size()]].position;

	return Vector2 { 0,0 };
}

void Level::addTile(const Tile& tile) {
	if (tile.x / tileSize > 123 || tile.x / tileSize < -124 || tile.y / tileSize > 123 || tile.y / tileSize < -124)return;

	for (auto it = _tiles.begin(); it != _tiles.end(); it++) //Check for existing tile
		if (it->x == tile.x && it->y == tile.y && it->layer == tile.layer)
			if (it->TileID != tile.TileID)
				_tiles.erase(it);
			else return;

	bool layerFound = false, IDFound = false, inIDRange = false;;
	auto it = _tiles.begin();

	for (it; it != _tiles.end(); it++) {
		if (tile.layer == it->layer) {
			layerFound = true;
			if (tile.TileID == it->TileID) {
				IDFound = true;
				if (tile.TileID != it->TileID || tile.x > it->x || (tile.x == it->x && tile.y > it->y))
					break;
			}
			else if (IDFound) break;
		}
		else if (layerFound) break;
	}
	_tiles.insert(it, tile);
}

void Level::removeTile(const Tile& tile) {
	for (auto it = _tiles.begin(); it != _tiles.end(); it++)
		if (it->layer == tile.layer && it->x == tile.x && it->y == tile.y) {
			_tiles.erase(it);
			return;
		}
}

void Level::addEntityData(const EntityData& data) {
	for (auto it = _entData.begin(); it != _entData.end(); it++)
		if (*it < data) {
			_entData.insert(it, data);
			return;
		}

	_entData.push_back(data);
}

void Level::removeEntityData(const EntityData& data) {
	_entData.erase(std::remove(_entData.begin(), _entData.end(), data), _entData.end());
}

bool Level::load(const char* path) {
	FileManager::readLevelFile(path, (int)tileSize, _tiles, _entData);

	return true;
}

bool Level::save(const char* path) {
	FileManager::writeLevelFile(_tiles, _entData, path, (int)tileSize);

	return true;
}

void Level::drawSprites(Camera2D& cam,int layer) {
	for (auto t = _tiles.begin(); t != _tiles.end(); t++)
		if (t->layer == layer)
			SpriteRenderer::drawSprite(*tileSheet, cam.getMin(), cam.getMax(), (float)t->x, (float)t->y, tileSize, tileSize, 0.0f, 8, t->TileID);
}

void Level::drawSprites(Camera2D& cam, int layer, Colour c) {
	for (auto t = _tiles.begin(); t != _tiles.end(); t++)
		if (t->layer == layer)
			SpriteRenderer::drawSprite(*tileSheet, cam.getMin(), cam.getMax(), (float)t->x, (float)t->y, tileSize, tileSize, c, 0.0f, 8, t->TileID);
}

void Level::drawEntitySprites() {
	for (auto t = _entData.begin(); t != _entData.end(); t++)
		SpriteRenderer::drawSprite(*editorTileSheet, (float)t->position.x, (float)t->position.y, tileSize, tileSize, 0.0f, 4, t->ID);
}

Tile* Level::rectOverlaps(Vector2f min, Vector2f max, int layer) {
	for (auto t = _tiles.begin(); t != _tiles.end(); t++) {
		if (t->layer == layer && !(max.x <= t->x || max.y <= t->y || min.x >= t->x + tileSize || min.y >= t->y + tileSize))
			return &(*t);
		if (t->layer > layer)
			break;
	}
	return NULL;
}
