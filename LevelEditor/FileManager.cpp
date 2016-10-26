#include "FileManager.h"
#include <Engine/Utility.h>
#include <fstream>


FileManager::FileManager() {

}


FileManager::~FileManager() {

}

using namespace std;

void FileManager::writeLevelFile(std::vector<Tile> tiles,const char* path) {

	ofstream stream(path);
	if (!stream.is_open())return;

	for (Tile t : tiles) {
		stream << t.TileID << ' ' << t.x << ' ' << t.y << (t.flag > 0 ? (char*)t.flag : "") << endl;
	}

	stream.close();
}