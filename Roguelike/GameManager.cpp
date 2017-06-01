#include "GameManager.h"

#include "GameData.h"

#include <Engine/ErrorHandling.h>
#include <Engine/GUI.h>
#include <Engine/SpriteRenderer.h>
#include <SDL/SDL.h>

using namespace GameData;

EntityContainer GameManager::_root;
bool GameManager::_updating;
Texture* GameManager::_tilesheet;
unsigned int GameManager::_currentTileIndex;

void GameManager::addEntity(Entity* obj) {
	_root.addEntity(obj);
}

void GameManager::update(float deltaTime) {
	runTime += deltaTime;
	////
	SDL_GetMouseState(&mousePosition.x, &mousePosition.y);
	mousePosition.y = screenDimensions.y - mousePosition.y;
	mouseOnGUI = GlobalUI::update(mousePosition.x, mousePosition.y);
	///////////////////////////////////////////////////////////////////////////

	_root.update(deltaTime);
}

void GameManager::renderObjects(Shader& shader) {
	_root.render(shader);
}

void GameManager::renderLevel(signed char lastLayer, bool resetIterator, const Rect_i& cameradimensions) {
	if (level)level->drawTiles(lastLayer, resetIterator, cameradimensions, *_tilesheet);
}
