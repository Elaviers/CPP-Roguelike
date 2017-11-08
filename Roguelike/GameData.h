#pragma once
#include "Game.h"
#include <Engine/Camera.h>
#include <Engine/Vector2.h>

namespace GameData {
	extern char* exedir;
	extern Game* gameInstance;

	extern Vector2i screenDimensions;
	extern Vector2i mousePosition;
	extern bool mouseOnGUI;

	extern float runTime;
	extern float timeScale;

	extern Camera* camera;
}
