#pragma once
#include "FileManager.h"
#include <Engine/Texture.h>

class Level
{
private:
	std::vector<Tile> _tiles;
	Tile _spawn;
public:
	Level();
	~Level();

	void drawSprites(Texture&);
	void drawEditorSprites(Texture&);
	void edit(Tile,bool = false);
	void setFlag(Tile t);
	void setSpawnPoint(int,int);

	bool save(const char*);
	bool load(const char*);
};

