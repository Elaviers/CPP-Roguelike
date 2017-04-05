#include "GameData.h"

namespace GameData {
	char* exedir;
	Game* gameInstance;

	Vector2 screenDimensions;
	Vector2 mousePosition;
	bool mouseOnGUI;

	float runTime;

	Camera2D* camera;
	Level* level;
}
