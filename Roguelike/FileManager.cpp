#include "FileManager.h"
#include "PropertySet.h"
#include "Types.h"

#include <Engine/Utility.h>
#include <fstream>
#include <iostream>
#include <iterator>

const unsigned char CHAR_OFFSET = 132;

using namespace std;

namespace LevelFlags {
	enum LevelFlags {
		LAYER = 0,
		TILEID = 1,
		X = 2,
		ENTLAYER = 7
	};
}

void FileManager::readFile(const char* Path, vector<StringPair>& arr)
{
	ifstream stream(Path);
	string str;

	if (!stream.is_open())return;

	arr.clear();

	while (getline(stream, str)) {
		StringPair s;
		int i = (int)str.find("=");
		s.Property = str.substr(0, i);
		s.Value = str.substr(i + 1, str.length() - i);
		arr.push_back(s);
	}

	stream.close();
}

bool FileManager::readBool(const vector<StringPair>& arr, const string& name) {
	for (StringPair p : arr)
		if (p.Property == name && p.Value == "true")
			return true;
	return false;
}

int FileManager::readInt(const vector<StringPair>& arr, const string& name) {
	for (StringPair p : arr)
		if (p.Property == name)
			return stoi(p.Value);

	return -1;
}

void FileManager::readLevelFile(const char* Path, vector<Tile>& tileList, vector<Entity*>& entityList)
{
	ifstream stream(Path, ios::binary | ios::in);
	stream >> std::noskipws;

	if (!stream.is_open())return;

	std::vector<uByte>buffer((istream_iterator<unsigned char>(stream)), istream_iterator<unsigned char>());

	std::cout << "(FileManager) : Beginning load..." << endl;
	tileList.clear();
	entityList.clear();

	bool force = true;
	bool placeEntity = false;

	unsigned char currentEntID, currentID;
	signed char currentLayer, currentX;

	auto it = buffer.begin();
	while (it < buffer.end()) {
		if (*it < 8) {
			if (*it == LevelFlags::LAYER) {
				currentLayer = *++it - CHAR_OFFSET;
				placeEntity = false;
				force = true;
				//it++;
				std::cout << "layer " << (int)currentLayer << '\n';
			}
			else if (*it == LevelFlags::ENTLAYER) {
				currentEntID = *++it;
				placeEntity = true;
				force = true;
				//it++;
				std::cout << "entid " << (int)currentEntID << '\n';
			}

			if (!placeEntity && (force || *it == LevelFlags::TILEID)) {
				currentID = *++it - CHAR_OFFSET;
				force = true;
				//it++;
				std::cout << u8"├──id " << (int)currentID << '\n';
			}
			if (force || *it == LevelFlags::X) {
				currentX = *++it - CHAR_OFFSET;
				force = false;
				std::cout << u8"│  ├──x " << (int)currentX << '\n';
				it++;
			}
		}

		if (!placeEntity) {
			tileList.push_back(Tile{ currentLayer, currentID, currentX, (*it - CHAR_OFFSET) });
			std::cout << u8"│  │  ├──y " << *it - CHAR_OFFSET << '\n';
			it++;
		}
		else {
			Entity* ent = Entity::createClassForID(currentEntID);
			static PropertySet properties;
			ent->GetProperties(properties);
			properties.getFromBuffer(it);
			ent->SetProperties(properties);
			properties.clear();
			ent->position = Vector2f((float)currentX, (float)(*it - CHAR_OFFSET));

			entityList.push_back(ent);

			std::cout << u8"│  │  ├──y " << *it - CHAR_OFFSET << '\n';
			it++;
			it++; //Skip null char (until newer levels are saved)
		}
	}

	stream.close();
}

void FileManager::writeLevelFile(const std::vector<Tile>& tiles, const std::vector<Entity*>& entities, const char* path) {

	ofstream stream(path, ios::binary | ios::out);
	if (!stream.is_open())return;

	bool force = true;
	vector<unsigned char> buffer;

	signed char currentLayer;
	unsigned char currentID;
	signed char currentX, currentY;

	for (Tile t : tiles) {
		//Values 0-7 are load flags
		if (force || t.layer != currentLayer) {
			buffer.push_back(LevelFlags::LAYER);//Flag : new Layer
			buffer.push_back(t.layer + CHAR_OFFSET);
			printf("push new layer: %d (%d)\n", (unsigned char)t.layer + CHAR_OFFSET, t.layer);
			currentLayer = t.layer;
			force = true;
		}
		if (force || t.id != currentID) {
			if (!force)buffer.push_back(LevelFlags::TILEID);//Flag : new TileID
			buffer.push_back(t.id + CHAR_OFFSET);
			currentID = t.id;
			printf("push new ID: %d (%d)\n", t.id + CHAR_OFFSET, t.id);
			force = true;
		}
		if (force || t.x != currentX) {
			if (!force)buffer.push_back(LevelFlags::X);//Flag : new X value
			buffer.push_back((unsigned char)t.x + CHAR_OFFSET);
			currentX = t.x;
			printf("push new x: %d (%d)\n", (unsigned char)t.x + CHAR_OFFSET, t.x);
			force = true;
		}
		if (force || t.y != currentY) {
			buffer.push_back((unsigned char)t.y + CHAR_OFFSET);
			currentY = t.y;
			printf("push new y: %d (%d)\n", (unsigned char)t.y + CHAR_OFFSET, t.y);
			force = false;
		}
	}

	force = true;

	currentX = currentY = currentID = 0;
	for (const Entity* e : entities) {
		if (force || e->getID() != currentID) {
			currentID = e->getID();
			buffer.push_back(LevelFlags::ENTLAYER);
			buffer.push_back(currentID);
			printf("push new entity layer: ID %d\n", currentID);
			force = true;
		}
		if (force || e->position.x != currentX) {
			currentX = (signed char)e->position.x;
			if (!force)buffer.push_back(LevelFlags::X);//Flag : new X value
			buffer.push_back((unsigned char)currentX + CHAR_OFFSET);
			printf("push new x: %d (%d)\n", (unsigned char)currentX + CHAR_OFFSET, currentX);
			force = true;
		}
		if (force || e->position.y != currentY) {
			currentY = (signed char)e->position.y;
			buffer.push_back((unsigned char)currentY + CHAR_OFFSET);

			static PropertySet entProperties;
			e->GetProperties(entProperties);
			entProperties.addToBuffer(buffer);
			entProperties.clear();

			

			//buffer.push_back(0);
			printf("push new y: %d (%d)\n", (unsigned char)currentY + CHAR_OFFSET, currentY);
			force = false;
		}
	}

	stream.write((const char*)buffer.data(), sizeof(unsigned char) * buffer.size());
	stream.close();

	std::printf("(DEBUG) saved %d tiles\n", (int)tiles.size());
}
