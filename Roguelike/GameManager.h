#pragma once
#include "Level.h"

#include <Engine/Camera2D.h>
#include <Engine/EntityContainer.h>
#include <vector>

class GameManager
{
private:
	static EntityContainer _root;
	static bool _updating;
public:
	static void addEntity(Entity* Object);

	static void update(float DeltaTime);
	static void renderLevel(int StartingLayer, int EndLayer);
	static void renderObjects(Shader& s);
};
