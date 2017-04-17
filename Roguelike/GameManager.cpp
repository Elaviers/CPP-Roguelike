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
	SDL_GetMouseState(&mousePosition.x, &mousePosition.y);
	mousePosition.y = screenDimensions.y - mousePosition.y;
	mouseOnGUI = GlobalUI::update(mousePosition.x, mousePosition.y);
	///////////////////////////////////////////////////////////////////////////

	_root.update(deltaTime);
}

void GameManager::renderLevel(signed char maxLayer, bool keepiterator) {
	if (!level) return;

	if (!keepiterator)
		_currentTileIndex = 0;

	auto end = GameData::level->tileData()->end();
	Vector2 cameraMin = GameData::camera->getMin(), cameraMax = GameData::camera->getMax();

	for (auto it = GameData::level->tileData()->begin() + _currentTileIndex; it->layer <= maxLayer && it != end; it++, _currentTileIndex++) {
		if (it->x * 64 < cameraMax.x && it->y * 64 < cameraMax.y && it->x * 64 + 64 > cameraMin.x && it->y * 64 + 64 > cameraMin.y)
			SpriteRenderer::drawSprite(*_tilesheet, it->x * 64, it->y * 64, 64, 64, 0.f, 8, it->id);
		//std::printf("draw %d\n",_currentTileIndex);
	}

	//for (int i = StartingLayer; i <= EndLayer; i++)
	//	level->drawSprites(*camera, i);
}

void GameManager::renderObjects(Shader& shader) {
	_root.render(shader);
}