#include "GameManager.h"

#include "GameData.h"

#include <Engine/ErrorHandling.h>
#include <Engine/GUI.h>
#include <SDL/SDL.h>

using namespace GameData;

EntityContainer GameManager::_root;
bool GameManager::_updating;

void GameManager::addEntity(Entity* obj) {
	_root.addEntity(obj);
}

void GameManager::update(float deltaTime) {
	SDL_GetMouseState(&mousePosition.x, &mousePosition.y);
	mousePosition.y = screenDimensions.y - mousePosition.y;
	mouseOnGUI = GlobalUI::update(mousePosition.x, mousePosition.y);
	///////////////////////////////////////////////////////////////////////////

	_root.update(deltaTime);
}

void GameManager::renderLevel(int StartingLayer, int EndLayer) {
	if (!level) return;

	for (int i = StartingLayer; i <= EndLayer; i++)
		level->drawSprites(*camera, i);
}

void GameManager::renderObjects(Shader& shader) {
	_root.render(shader);
}