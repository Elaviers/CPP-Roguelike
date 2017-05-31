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

void GameManager::renderLevel(signed char maxLayer, bool keepiterator) {
	if (!level) return;

	if (!keepiterator)
		_currentTileIndex = 0;

	auto end = GameData::level->tileData()->end();
	Vector2i cameraMin = GameData::camera->getMin(), cameraMax = GameData::camera->getMax();

	for (auto it = GameData::level->tileData()->begin() + _currentTileIndex;  it != end && it->layer <= maxLayer; it++, _currentTileIndex++) {
		if (it->x * 64 < cameraMax.x && it->y * 64 < cameraMax.y && it->x * 64 + 64 > cameraMin.x && it->y * 64 + 64 > cameraMin.y)
			SpriteRenderer::drawSprite(*_tilesheet, (float)(it->x * 64), (float)(it->y * 64), 64, 64, 0.f, 8, it->id);
	}
}

void GameManager::renderObjects(Shader& shader) {
	_root.render(shader);
}