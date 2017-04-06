#pragma once
#include "Game.h"
#include "Level.h"

#include <Engine/Camera2D.h>
#include <Engine/Entity.h>
#include <vector>

class Game;

class GameManager
{
private:
	static std::vector<Entity*> _entities, _pending;
	static bool _updating;
public:
	static void addEntity(Entity* Object);

	static void update();
	static void renderLevel(int StartingLayer, int EndLayer);
	static void renderObjects(Shader& s, float DeltaTime);
};
