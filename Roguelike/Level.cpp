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

const float tileSize = 64;

Vector2 Level::getSpawnPoint() {
	return Vector2 { (float)_spawn.x + tileSize / 2, (float)_spawn.y + tileSize / 2 };
}

//Editing functions
void Level::edit(Tile tile, bool remove) {
	if (tile.x / tileSize > 119 || tile.x / tileSize < -119 || tile.y / tileSize > 119 || tile.y / tileSize < -119)return;

	for (int i = 0; i < _tiles.size(); i++)
		if (_tiles[i].x == tile.x && _tiles[i].y == tile.y)
			_tiles.erase(_tiles.begin() + i);//Remove tile if it exists in level

	if (!remove) {
		int index = 0;
		bool inIDRange = false;
		for (Tile t : _tiles) {
			if (tile.TileID == t.TileID) {
				inIDRange = true;
				if (tile.x > t.x || (tile.x == t.x && tile.y > t.y)) {
					break;
				}
			}
			else if (inIDRange) { printf("OVERRIDDEN\n"); break; }

			index++;
		}
		_tiles.emplace(_tiles.begin() + index, tile);
		if (index > 0)printf("Tile edited and placed at %d (after %d: %f, %f)\n", index, _tiles[index - 1].TileID, _tiles[index - 1].x / tileSize, _tiles[index - 1].y / tileSize);
	}
}

void Level::setFlag(Tile tile, char flag) {
	for (int i = 0; i < _tiles.size(); i++) {
		if (_tiles[i].x == tile.x && _tiles[i].y == tile.y) {
			_tiles[i].flag = flag;
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

	for (Tile& t : _tiles) {
		if (t.flag == 's') {
			_spawn.x = t.x;
			_spawn.y = t.y;
			t.flag = 0;
		}
	}

	return true;
}

bool Level::save(const char* path) {
	setFlag(_spawn, 's');

	FileManager::writeLevelFile(_tiles, path);

	setFlag(_spawn, 0);
	return true;
}

void Level::drawSprites(Camera2D& cam) {
	for (Tile t : _tiles)
		if (t.TileID > -1)
			SpriteRenderer::drawSprite(*tileSheet, cam.Corner1(), cam.Corner2(), (float)t.x, (float)t.y, tileSize, tileSize, 0.0f, 8, t.TileID);
}

void Level::drawEditorSprites() {
	for (Tile t : _tiles)
		if (t.TileID < 0)
			SpriteRenderer::drawSprite(*editorTileSheet, (float)t.x, (float)t.y, tileSize, tileSize, 0.0f, 4, 1);

	SpriteRenderer::drawSprite(*editorTileSheet, (float)_spawn.x, (float)_spawn.y, tileSize, tileSize, 0.0f, 4);
}