#include "Level.h"

#include "FileManager.h"

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

//Editing functions
void Level::edit(Tile tile, bool remove) {
	if (tile.x / tileSize > 123 || tile.x / tileSize < -124 || tile.y / tileSize > 123 || tile.y / tileSize < -124)return;

	for (int i = 0; i < _tiles.size(); i++)
		if (_tiles[i].x == tile.x && _tiles[i].y == tile.y && _tiles[i].layer == tile.layer)
			if (!remove && _tiles[i].TileID == tile.TileID)
				return; //If tile is identical then return
			else
				_tiles.erase(_tiles.begin() + i);
				//_tiles.erase(_tiles.begin() + i);//Remove tile if it exists in level

	bool layerFound = false, IDFound = false;

	if (!remove) {
		int index = 0;
		bool inIDRange = false;
		for (index; index < _tiles.size();index++) {
			if (tile.layer == _tiles[index].layer) {
				layerFound = true;
				if (tile.TileID == _tiles[index].TileID) {
					IDFound = true;
					if (tile.TileID != _tiles[index].TileID || tile.x > _tiles[index].x || (tile.x == _tiles[index].x && tile.y > _tiles[index].y))
						break;
				}
				else if (IDFound) break;
			}
			else if (layerFound) break;
		}
		_tiles.emplace(_tiles.begin() + index, tile);
		printf("Tile placed at index %d",index);
		if (index > 0)printf(" (after %d: %f, %f)\n", _tiles[index - 1].TileID, _tiles[index - 1].x / tileSize, _tiles[index - 1].y / tileSize);
		else printf("\n");
	}
}

void Level::addEntity(const Entity& ent) {
	EntityData data{ ent.ID, ent.getData(), Vector2{ (int)ent.position.x, (int)ent.position.y } };

	for (auto it = _entData.begin(); it < _entData.end(); it++)
		if (*it < data) {
			_entData.insert(it, data);
			return;
		}

	_entData.push_back(data);
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
