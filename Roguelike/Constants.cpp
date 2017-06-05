#include "Constants.h"

const char* Constants::font = "Game/Fonts/font.ttf";
const char* Constants::font_editor = "Game/Fonts/arial.ttf";

#include <Engine/Registry.h>
#include "Spawnpoint.h"
#include "LevelConnector.h"

void Constants::create_registry() {
	EntityRegistry::add<SpawnPoint>(0, "Spawn Point");
	EntityRegistry::add<LevelConnector>(1, "Level Connector");
}
