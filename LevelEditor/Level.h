#pragma once
#include "FileManager.h"
#include <Engine/Texture.h>
#include <Engine/CAMERA2D.H>

class Level
{
private:
	std::vector<Tile> _tiles;
	Tile _spawn;
public:
	Level();
	~Level();

	void drawSprites(Texture&,Camera2D&);
	void drawEditorSprites(Texture&);
	void edit(Tile,bool = false);
	void setFlag(Tile t,char);
	void setSpawnPoint(int,int);

	bool save(const char*);
	bool load(const char*);
};

