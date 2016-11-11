#include "FileManager.h"
#include <Engine/Utility.h>
#include <fstream>

#define CHAR_OFFSET (8 + 127 / 2)

using namespace std;

void FileManager::writeLevelFile(std::vector<Tile> tiles,const char* path) {

	ofstream stream(path, ios::binary | ios::out);
	if (!stream.is_open())return;

	int currentIndex = 0, currentX = 0, currentY = 0;
	bool force = true;

	printf("(DEBUG) saved %d tiles\n",tiles.size());

	vector<unsigned char> buffer;

	for (Tile t : tiles) {
		//Values 0-7 are load flags
		if (t.TileID != currentIndex || force) {
			buffer.push_back(0);//Flag : new TileID
			buffer.push_back(t.TileID + CHAR_OFFSET);
			currentIndex = t.TileID;
			force = true;
		}
		if (t.x != currentX || force) {
			if (!force)buffer.push_back(1);//Flag : new X value
			buffer.push_back(t.x / 64 + CHAR_OFFSET);//Offset by 8 for flag count
			currentX = t.x;
			force = true;
		}
		if (t.y != currentY || force) {
			buffer.push_back(t.y / 64 + CHAR_OFFSET);//Offset by 8 for flag count
			currentY = t.y;
			force = false;
			if (t.flag > 0) {
				buffer.push_back(2);//Flag : set Tile Flag
				buffer.push_back(t.flag + 8);//Add 8 instead of char offset because we don't have negative values
			}
		}
	}

	stream.write((const char*)buffer.data(), sizeof(unsigned char) * buffer.size());
	stream.close();
}

vector<Tile> FileManager::readLevelFile(const char* Path, int unitSize)
{
	ifstream stream(Path,ios::binary | ios::in);

	if (!stream.is_open())return (vector<Tile>)NULL;
	std::string str((istreambuf_iterator<char>(stream)), istreambuf_iterator<char>());

	Tile current;
	vector <Tile> returnvalue;


	for (int i = 0; i < str.length();i++) {
		if (str[i] < 8) {
			switch (str[i]) {
			case 0://New TileID
				current.TileID = str[++i] - CHAR_OFFSET;
				current.x = (str[++i] - CHAR_OFFSET) * 64;
				break;
			case 1://New X
				current.x = (str[++i] - CHAR_OFFSET) * 64;
				break;
			case 2:
				returnvalue.back().flag = str[++i] - 8;//Subtract 8 instead of offset
				break;
			}
			continue;
		}

		current.y = (str[i] - CHAR_OFFSET) * 64;
		returnvalue.push_back(current);

		if (current.flag > 0)
			current.flag = 0;
	}

	stream.close();
	return returnvalue;
}