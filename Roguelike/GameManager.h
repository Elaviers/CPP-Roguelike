#pragma once
#include "EntityContainer.h"
#include "Level.h"

#include <Engine/Camera2D.h>
#include <Engine/ResourceManager.h>
#include <vector>

class GameManager
{
private:
	static EntityContainer _root;
	static bool _updating;

	static Texture* _tilesheet;

	static unsigned int _currentTileIndex;
public:
	static void addEntity(Entity* Object);

	static void update(float DeltaTime);
	static void renderLevel(signed char lastLayer, bool resetIterator, const Rect_i& cameradimensions);
	static void renderObjects(Shader& s);

	static void setTileTexture(const char* path) { _tilesheet = ResourceManager::getTextureRef(path); };
};
