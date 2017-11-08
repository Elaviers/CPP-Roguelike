#include "Constants.h"

const char* Constants::font = "Game/Fonts/font.ttf";
const char* Constants::font_editor = "Game/Fonts/arial.ttf";

#include <Engine/Registry.h>
#include "E_Spawnpoint.h"
#include "E_LevelConnector.h"

void Constants::create_registry() {
	EntityRegistry::add<E_SpawnPoint>(0, "Spawn Point");
	EntityRegistry::add<E_LevelConnector>(1, "Level Connector");
}
