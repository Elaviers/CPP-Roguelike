#pragma once

#include <Engine/Texture.h>
#include <Engine/Camera2D.h>
#include <vector>
#include <Engine/Vertex.h>

struct Tile {
	int TileID;
	int x, y;
	char flag;
};

class Level
{
private:
	std::vector<Tile> _tiles;
	Tile _spawn;
public:
	Level();
	~Level();

	Vector2 getSpawnPoint();
	Texture *tileSheet, *editorTileSheet;

	void drawSprites(Camera2D&);
	void drawEditorSprites();
	void edit(Tile, bool = false);
	void setFlag(Tile t, char);
	void setSpawnPoint(int, int);

	bool save(const char*);
	bool load(const char*);
};

