#include "GameManager.h"

#include "GameData.h"

#include <Engine/ErrorHandling.h>
#include <Engine/GUI.h>
#include <SDL/SDL.h>

using namespace GameData;

std::vector<Entity*> GameManager::_entities, GameManager::_pending;
bool GameManager::_updating;

void GameManager::addEntity(Entity* obj) {
	if (!_updating)_entities.push_back(obj);
	else _pending.push_back(obj);
}

void GameManager::update() {
	SDL_GetMouseState(&mousePosition.x,&mousePosition.y);
	mousePosition.y = screenDimensions.y - mousePosition.y;
	mouseOnGUI = GlobalUI::update(mousePosition.x,mousePosition.y);
	///////////////////////////////////////////////////////////////////////////

	if (_pending.size() > 0) {
		for (auto it = _pending.begin(); it != _pending.end(); it++)
			_entities.push_back(*it);
		_pending.clear();
	}

	_updating = true;

	for (auto it = _entities.begin(); it != _entities.end(); it++)
		(*it)->update();

	_updating = false;
}

void GameManager::renderLevel(int StartingLayer, int EndLayer) {
	if (!level) return;

	for (int i = StartingLayer; i <= EndLayer; i++)
		level->drawSprites(*camera,i);
}

void GameManager::renderObjects(Shader& shader, float DeltaTime) {
	for (auto it = _entities.begin(); it != _entities.end(); it++)
		(*it)->render(shader, DeltaTime);
}