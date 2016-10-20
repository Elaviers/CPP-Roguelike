#pragma once
#include <fstream>
#include <string>
#include <vector>

struct StringPair {
	std::string Property, Value;
};

struct Tile {
	int TileID;
	float x, y;
	char flag;
};

using namespace std;

namespace FileManager
{
	vector<StringPair> readFile(const char* FilePath);
	vector<Tile> readLevelFile(const char* FilePath, int);

	bool readBool(vector<StringPair> Properties,string PropertyName);
	int readInt(vector<StringPair> Properties,string PropertyName);
}