#pragma once

#include <Engine/Texture.h>
#include <Engine/Camera2D.h>
#include <vector>
#include <Engine/Vertex.h>
#include "Tile.h"

namespace TileFlags {
	enum TileFlag {
		SPAWNPOINT = 0x01
	};
}

class Level
{
private:
	std::vector<Tile> _tiles;
	Tile _spawn;
public:
	Level();
	~Level();

	Vector2f getSpawnPoint();
	Texture *tileSheet, *editorTileSheet;

	Tile* getData();

	void drawSprites(Camera2D&,int layer);
	void drawEditorSprites();
	void edit(Tile, bool = false);
	void setFlag(Tile t, char);
	void setSpawnPoint(int, int);

	bool save(const char*);
	bool load(const char*);

	Tile* rectOverlaps(Vector2f min, Vector2f max, int layer);
};

