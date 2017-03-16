#pragma once

#include <Engine/Camera2D.h>
#include <Engine/GameObject.h>
#include "Level.h"

#include <vector>

#include "Game.h"

class Game;

class GameManager
{
private:
	static std::vector<GameObject*> Objects;
public:
	static Game* gameInstance;

	static Vector2 screenDimensions;
	static Vector2 mousePosition;
	static bool mouseOnGUI;

	static float runTime;

	static Camera2D* camera;
	static Level* level;

	static void addObject(GameObject* Object);

	static void update();
	static void renderLevel(int StartingLayer, int EndLayer);
	static void renderObjects(Shader& s, float DeltaTime);
};

