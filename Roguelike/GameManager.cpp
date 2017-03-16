#include "GameManager.h"
#include <Engine/ErrorHandling.h>
#include <SDL/SDL.h>
#include <Engine/GUI.h>

Game* GameManager::gameInstance;
Vector2 GameManager::screenDimensions;
Vector2 GameManager::mousePosition = Vector2 { 0, 0 };
bool GameManager::mouseOnGUI;

float GameManager::runTime;

Camera2D* GameManager::camera;
Level* GameManager::level;

std::vector<GameObject*> GameManager::Objects;

void GameManager::addObject(GameObject* obj) {
	Objects.push_back(obj);
}

void GameManager::update() {
	SDL_GetMouseState(&mousePosition.x,&mousePosition.y);
	mousePosition.y = screenDimensions.y - mousePosition.y;
	mouseOnGUI = GlobalUI::updateMousePosition(mousePosition.x,mousePosition.y);

	for (GameObject* Object : Objects)
		Object->update();
}

void GameManager::renderLevel(int StartingLayer, int EndLayer) {
	if (!level) return;

	for (int i = StartingLayer; i <= EndLayer; i++)
		level->drawSprites(*camera,i);
}

void GameManager::renderObjects(Shader& shader, float DeltaTime) {
	for (GameObject* Object : Objects) {
		Object->render(shader, DeltaTime);
	}
}