#include "GameData.h"

namespace GameData {
	char* exedir;
	Game* gameInstance;

	Vector2i screenDimensions;
	Vector2i mousePosition;
	bool mouseOnGUI;

	float runTime;
	float timeScale = 1.0f;

	Camera* camera;
}
