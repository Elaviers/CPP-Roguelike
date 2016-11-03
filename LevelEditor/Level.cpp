#include "Level.h"
#include <Engine/SpriteRenderer.h>

Level::Level() : _spawn(Tile {-1,0,0,'s'})
{
}


Level::~Level()
{
}

void Level::edit(Tile tile,bool remove) {
	for (int i = 0; i < _tiles.size(); i++)
		if (_tiles[i].x == tile.x && _tiles[i].y == tile.y) {
			if (!remove)_tiles[i] = tile;
			else _tiles.erase(_tiles.begin() + i);
			return;
		}

	if (!remove)_tiles.push_back(tile);
}

void Level::setFlag(Tile tile) {
	for (int i = 0; i < _tiles.size(); i++) {
		if (_tiles[i].x == tile.x && _tiles[i].y == tile.y) {
			_tiles[i].flag = tile.flag;
			return;
		}
	}

	_tiles.push_back(tile);
}

void Level::setSpawnPoint(int x,int y) {
	_spawn.x = (float)x; _spawn.y = (float)y;
}

bool Level::load(const char* path) {
	_tiles = FileManager::readLevelFile(path,64);

	for (Tile t : _tiles)
		if (t.flag == 's') {
			_spawn.x = t.x;
			_spawn.y = t.y;
			edit(t, true);
		}

	return true;
}

bool Level::save(const char* path) {
	setFlag(_spawn);

	FileManager::writeLevelFile(_tiles,path);
	return true;
}

void Level::drawSprites(Texture& _tex) {
	for (Tile t : _tiles)
		SpriteRenderer::drawSprite(_tex, t.x, t.y, 64, 64, 0, 8, t.TileID);
}

void Level::drawEditorSprites(Texture& _tex) {
	SpriteRenderer::drawSprite(_tex,_spawn.x,_spawn.y,64,64,0,4);
}