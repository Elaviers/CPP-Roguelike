#include "FileManager.h"
#include <Engine/Utility.h>
#include <fstream>

using namespace std;

void FileManager::writeLevelFile(std::vector<Tile> tiles,const char* path) {

	ofstream stream(path);
	if (!stream.is_open())return;


	for (Tile t : tiles) {
		stream << t.TileID << ' ' << t.x / 64 << ' ' << t.y / 64;
		if (t.flag > 0)stream << ' ' << t.flag;
		stream << endl;
	}

	stream.close();
}

vector<Tile> FileManager::readLevelFile(const char* Path, int unitSize)
{
	ifstream stream(Path);
	string str;

	if (!stream.is_open())return (vector<Tile>)NULL;

	vector<Tile> returnvalue;
	while (getline(stream, str)) {
		if (str.length() > 0 && str[0] != '|') {
			vector<string> elements;
			Utility::splitString(str, ' ', elements);
			if (elements.size() >= 3) {
				for (int s = 0; s < elements.size(); s++)
					printf("%s | ", elements[s].c_str());
				printf("\n");

				Tile t;
				t.TileID = stoi(elements[0].c_str());
				t.x = (float)unitSize * stoi(elements[1].c_str());
				t.y = (float)unitSize * stoi(elements[2].c_str());
				if (elements.size() >= 4)
					t.flag = elements[3][0];
				else t.flag = 0;

				returnvalue.push_back(t);
			}
		}
	}

	stream.close();
	return returnvalue;
}