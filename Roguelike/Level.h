#pragma once

#include "FileManager.h"
#include <Engine/ResourceManager.h>
#include <Engine/Texture.h>
#include <Engine/SpriteRenderer.h>

struct SpawnPoint {
	int x, y;
};

class Level
{
private:
	std::vector<Tile> _tiles;
	Texture _tex;
public:
	Level();
	~Level();

	void init(const char* path);
	SpawnPoint getSpawnPoint();
	void render(Shader s);
};

