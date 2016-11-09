#include "FileManager.h"
#include <Engine/Utility.h>
#include <fstream>

using namespace std;

void FileManager::writeLevelFile(std::vector<Tile> tiles,const char* path) {

	ofstream stream(path, ios::binary | ios::out);
	if (!stream.is_open())return;

	int currentIndex = 0, currentX = 0, currentY = 0;
	bool force = true;

	printf("(DEBUG) saved %d tiles\n",tiles.size());

	vector<char> buffer;

	for (Tile t : tiles) {
		/*if (t.TileID != currentIndex || force) {
			stream << t.TileID << endl;
			currentIndex = t.TileID;
		}
		if (t.x != currentX || force) {
			stream << "\t" << t.x / 64 << endl;
			currentX = t.x;
			force = true;
		}
		if (t.y != currentY || force) {
			stream << "\t\t" << t.y / 64 << endl;
			currentY = t.y;
			force = false;
		}*///OLD

		//Values 0-7 are load flags
		if (t.TileID != currentIndex || force) {
			buffer.push_back(0);//Flag : new TileID
			buffer.push_back(t.TileID + 8);
			currentIndex = t.TileID;
			force = true;
		}
		if (t.x != currentX || force) {
			if (!force)buffer.push_back(1);//Flag : new X value
			buffer.push_back(t.x / 64 + 8 + 127 / 2);//Offset by 8 for flag count
			currentX = t.x;
			force = true;
		}
		if (t.y != currentY || force) {
			buffer.push_back(t.y / 64 + 8 + 127 / 2);//Offset by 8 for flag count
			currentY = t.y;
			force = false;
		}
	}

	stream.write(buffer.data(),buffer.size());

	stream.close();
}

vector<Tile> FileManager::readLevelFile(const char* Path, int unitSize)
{
	ifstream stream(Path);

	if (!stream.is_open())return (vector<Tile>)NULL;
	std::string str((istreambuf_iterator<char>(stream)), istreambuf_iterator<char>());

	Tile current;
	vector <Tile> returnvalue;

	int i = 0;
	bool first = true;
	while (i < str.length()) {
		if (str[i] < 8) {
			switch (str[i]) {
			case 0://New TileID
				current.TileID = str[++i] - 8;
			case 1://New X
				//Comes here after case 0
				current.x = (str[++i] - (8 + 127/2)) * 64;
				i++;
				break;
			}
			continue;
		}

		current.y = (str[i++] - (8 + 127/2)) * 64;
		returnvalue.push_back(current);
	}

	stream.close();
	return returnvalue;
	return (vector<Tile>)NULL;
}

int tabCount(string str) {
	int i = 0;
	while (str[i] == '\t')
		i++;
	return i;
}