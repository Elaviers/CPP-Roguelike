#pragma once

struct Tile {
	int layer;
	int TileID;
	int x, y;
};

bool operator<(const Tile& a,const Tile& b);
