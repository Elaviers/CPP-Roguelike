#include "FileManager.h"
#include <fstream>
#include <iostream>
#include <iterator>
#include <Engine/Utility.h>

const int CHAR_OFFSET = 132;

using namespace std;

vector<StringPair> FileManager::readFile(const char* Path)
{
	ifstream stream(Path);
	string str;

	if (!stream.is_open())return (vector<StringPair>)NULL;

	vector<StringPair> returnvalue;
	while (getline(stream, str)) {
		StringPair s;
		int i = (int)str.find("=");
		s.Property = str.substr(0, i);
		s.Value = str.substr(i+1,str.length() - i);
		returnvalue.push_back(s);
	}

	stream.close();
	return returnvalue;
}

bool FileManager::readBool(vector<StringPair> arr, string name) {
	for (StringPair p : arr)
		if (p.Property == name && p.Value == "true")
			return true;
	return false;
}

int FileManager::readInt(vector<StringPair> arr, string name) {
	for (StringPair p : arr)
		if (p.Property == name)
			return stoi(p.Value);

	return -1;
}

vector<Tile> FileManager::readLevelFile(const char* Path, int unitSize)
{
	ifstream stream(Path, ios::binary | ios::in);
	stream >> std::noskipws;

	if (!stream.is_open())return (vector<Tile>)NULL;

	std::vector<unsigned char>buffer((istream_iterator<unsigned char>(stream)), istream_iterator<unsigned char>());

	Tile current;
	vector <Tile> returnvalue;

	std::cout << "(FileManager) : Beginning load..." << endl;

	for (int i = 0; i < buffer.size(); i++) {
		if (buffer[i] < 8) {
			switch (buffer[i]) {
			case 0://New Layer
				current.layer = buffer[++i] - CHAR_OFFSET;
				std::wcout << "Layer:" << current.layer << endl;
			case 1://New TileID
				current.TileID = buffer[++i] - CHAR_OFFSET;
				std::wcout << u8"├──tileID:" << current.TileID << std::endl;
			case 2://New X
				current.x = (buffer[++i] - CHAR_OFFSET) * unitSize;
				std::wcout << u8"│  ├──x:" << current.x << endl;
				break;
			case 3://Flagged Tile
				returnvalue.back().flag = buffer[++i];
				std::wcout << u8"│  │  │  ├──flag:" << (char)(buffer[i]) << endl;
				break;
			}
			continue;
		}

		current.y = (buffer[i] - CHAR_OFFSET) * unitSize;
		std::wcout << u8"│  │  ├──y:" << current.y << endl;
		returnvalue.push_back(current);

		if (current.flag > 0)
			current.flag = 0;
	}

	std::cout << "Done!\n";

	stream.close();
	return returnvalue;
}

void FileManager::writeLevelFile(std::vector<Tile> tiles, const char* path, int unitSize) {

	ofstream stream(path, ios::binary | ios::out);
	if (!stream.is_open())return;

	int currentLayer, currentIndex, currentX, currentY;
	bool force = true;

	std::printf("(DEBUG) saved %d tiles\n", (int)tiles.size());

	vector<unsigned char> buffer;

	for (Tile t : tiles) {
		//Values 0-7 are load flags
		if (force || t.layer != currentLayer) {
			buffer.push_back(0);//Flag : new Layer
			buffer.push_back(t.layer + CHAR_OFFSET);
			printf("push new layer: %d (%d)\n",t.layer + CHAR_OFFSET, t.layer);
			currentLayer = t.layer;
			force = true;
		}
		if (force || t.TileID != currentIndex) {
			if (!force)buffer.push_back(1);//Flag : new TileID
			buffer.push_back(t.TileID + CHAR_OFFSET);
			currentIndex = t.TileID;
			printf("push new ID: %d (%d)\n", t.TileID + CHAR_OFFSET, t.TileID);
			force = true;
		}
		if (force || t.x != currentX) {
			if (!force)buffer.push_back(2);//Flag : new X value
			buffer.push_back(t.x / unitSize + CHAR_OFFSET);
			currentX = (int)t.x;
			printf("push new x: %d (%d)\n", t.x / unitSize + CHAR_OFFSET, t.x);
			force = true;
		}
		if (force || t.y != currentY) {
			buffer.push_back(t.y / unitSize + CHAR_OFFSET);
			currentY = (int)t.y;
			printf("push new y: %d (%d)\n", t.y / unitSize + CHAR_OFFSET, t.y);
			force = false;
			if (t.flag > 0) {
				buffer.push_back(3);//Flag : set Tile Flag
				buffer.push_back(t.flag);//Can't be negative, so don't add char_offset
				printf("Push new flag: %c\n",t.flag);
			}
		}
	}

	stream.write((const char*)buffer.data(), sizeof(unsigned char) * buffer.size());
	stream.close();
}