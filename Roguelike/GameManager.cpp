#include "GameManager.h"

#include "GameData.h"

#include <Engine/ErrorHandling.h>
#include <Engine/GUI.h>
#include <SDL/SDL.h>

using namespace GameData;

std::vector<Entity*> GameManager::Entities;

void GameManager::addEntity(Entity* obj) {
	Entities.push_back(obj);
}

void GameManager::update() {
	SDL_GetMouseState(&mousePosition.x,&mousePosition.y);
	mousePosition.y = screenDimensions.y - mousePosition.y;
	mouseOnGUI = GlobalUI::update(mousePosition.x,mousePosition.y);

	for (auto it = Entities.begin(); it < Entities.end(); it++)
		(*it)->update();
}

void GameManager::renderLevel(int StartingLayer, int EndLayer) {
	if (!level) return;

	for (int i = StartingLayer; i <= EndLayer; i++)
		level->drawSprites(*camera,i);
}

void GameManager::renderObjects(Shader& shader, float DeltaTime) {
	for (auto it = Entities.begin(); it < Entities.end(); it++)
		(*it)->render(shader, DeltaTime);
}