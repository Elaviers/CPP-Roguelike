#include "Level.h"
#include "FileManager.h"

#include <Engine/SpriteRenderer.h>
#include <Engine/ResourceManager.h>

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

Vector2f Level::getSpawnPoint() {
	return Vector2f { (float)_spawn.x + tileSize / 2, (float)_spawn.y + tileSize / 2 };
}

//Editing functions
void Level::edit(Tile tile, bool remove) {
	if (tile.x / tileSize > 123 || tile.x / tileSize < -124 || tile.y / tileSize > 123 || tile.y / tileSize < -124)return;

	for (auto t = _tiles.begin(); t != _tiles.end(); t++)
		if (t->x == tile.x && t->y == tile.y && t->layer == tile.layer)
			if (!remove && t->TileID == tile.TileID)
				return; //If tile is identical then return
			else
				delete &(*t);
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

void Level::setFlag(Tile tile, char flag) {
	for (auto t = _tiles.begin(); t != _tiles.end(); t++) {
		if (t->x == tile.x && t->y == tile.y) {
			t->flag = flag;
			return;
		}
	}

	tile.flag = flag;
	edit(tile);
}

void Level::setSpawnPoint(int x, int y) {
	_spawn.x = x; _spawn.y = y;
}

bool Level::load(const char* path) {
	_tiles = FileManager::readLevelFile(path, (int)tileSize);

	for (auto t = _tiles.begin(); t != _tiles.end(); t++) {
		if (t->flag & TileFlags::SPAWNPOINT) {
			_spawn.x = t->x;
			_spawn.y = t->y;
			t->flag = 0;
		}
	}

	return true;
}

bool Level::save(const char* path) {
	setFlag(_spawn, TileFlags::SPAWNPOINT);

	FileManager::writeLevelFile(_tiles, path, 64);

	setFlag(_spawn, 0);
	return true;
}

void Level::drawSprites(Camera2D& cam,int layer) {
	for (auto t = _tiles.begin(); t != _tiles.end(); t++)
		if (t->TileID >= 0 && t->layer == layer)
			SpriteRenderer::drawSprite(*tileSheet, cam.getMin(), cam.getMax(), (float)t->x, (float)t->y, tileSize, tileSize, 0.0f, 8, t->TileID);
}

void Level::drawEditorSprites() {
	for (auto t = _tiles.begin(); t != _tiles.end(); t++)
		if (t->TileID < 0)
			SpriteRenderer::drawSprite(*editorTileSheet, (float)t->x, (float)t->y, tileSize, tileSize, 0.0f, 4, 1);

	SpriteRenderer::drawSprite(*editorTileSheet, (float)_spawn.x, (float)_spawn.y, tileSize, tileSize, 0.0f, 4);
}

Tile* Level::rectOverlaps(Vector2f min, Vector2f max, int layer) {
	for (auto t = _tiles.begin(); t != _tiles.end(); t++) {
		if (t->layer == layer && !(max.x <= t->x || max.y <= t->y || min.x >= t->x + 64 || min.y >= t->y + 64))
			return &(*t);
		if (t->layer > layer)
			break;
	}
	return NULL;
}
