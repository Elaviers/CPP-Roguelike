#pragma once

#include <Engine/Texture.h>
#include <Engine/Camera2D.h>
#include <vector>
#include <Engine/Vertex.h>
#include "Tile.h"
#include "Entity.h"

class Level
{
private:
	std::vector<Tile> _tiles;
	std::vector<EntityData> _entData;
public:
	Level();
	~Level();

	Vector2 getSpawnPoint();
	Texture *tileSheet, *editorTileSheet;

	Tile* getData();

	void drawSprites(Camera2D&,int layer);
	void drawSprites(Camera2D&, int layer, Colour c);
	void drawEntitySprites();
	void edit(Tile, bool = false);

	void addEntity(const Entity&);

	bool save(const char*);
	bool load(const char*);

	Tile* rectOverlaps(Vector2f min, Vector2f max, int layer);
};

