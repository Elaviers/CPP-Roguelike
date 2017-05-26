#pragma once
#include "Game.h"
#include "LevelData.h"

#include <Engine/Camera2D.h>
#include <Engine/Vector2.h>

namespace GameData {
	extern char* exedir;
	extern Game* gameInstance;

	extern Vector2 screenDimensions;
	extern Vector2 mousePosition;
	extern bool mouseOnGUI;

	extern float runTime;

	extern Camera2D* camera;
	extern LevelData* level;
}
