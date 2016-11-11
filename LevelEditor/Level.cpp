#include "Level.h"
#include <Engine/SpriteRenderer.h>

Level::Level() : _spawn(Tile {-1,0,0})
{
}


Level::~Level()
{
}

void Level::edit(Tile tile,bool remove) {
	if (tile.x/64 > 119 || tile.x/64 < -119 || tile.y/64 > 119 || tile.y/64 < -119)return;

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
		if (index > 0)printf("Tile edited and placed at %d (after %d: %f, %f)\n",index,_tiles[index-1].TileID, _tiles[index - 1].x / 64, _tiles[index - 1].y / 64);
	}
}

void Level::setFlag(Tile tile,char flag) {
	for (int i = 0; i < _tiles.size(); i++) {
		if (_tiles[i].x == tile.x && _tiles[i].y == tile.y) {
			_tiles[i].flag = flag;
			return;
		}
	}

	tile.flag = flag;
	edit(tile);
}

void Level::setSpawnPoint(int x,int y) {
	_spawn.x = (float)x; _spawn.y = (float)y;
}

bool Level::load(const char* path) {
	_tiles = FileManager::readLevelFile(path,64);

	for (Tile& t : _tiles) {
		if (t.flag == 's') {
			_spawn.x = t.x;
			_spawn.y = t.y;
			t.flag = 0;
		}
		printf("%f\n",t.y);
	}

	return true;
}

bool Level::save(const char* path) {
	setFlag(_spawn,'s');

	FileManager::writeLevelFile(_tiles,path);

	setFlag(_spawn,0);
	return true;
}

void Level::drawSprites(Texture& _tex,Camera2D& cam) {

	for (Tile t : _tiles)
		if (t.TileID > -1)
			SpriteRenderer::drawSprite(_tex, cam.Corner1(), cam.Corner2(), t.x, t.y, 64, 64, 0, 8, t.TileID);
}

void Level::drawEditorSprites(Texture& _tex) {
	for (Tile t : _tiles)
		if (t.TileID < 0)
			SpriteRenderer::drawSprite(_tex,t.x,t.y,64,64,0,4,1);

	SpriteRenderer::drawSprite(_tex,_spawn.x,_spawn.y,64,64,0,4);
}