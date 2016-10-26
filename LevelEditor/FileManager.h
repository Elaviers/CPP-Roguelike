#pragma once
#include <vector>

struct Tile {
	int TileID;
	float x, y;
	char flag;
};

class FileManager
{
public:
	FileManager();
	~FileManager();

	static void writeLevelFile(std::vector<Tile> tiles,const char* path);
};

