#include "Controller.h"
#include <Engine/SpriteRenderer.h>
#include <Engine/ResourceManager.h>

void Controller::init() {
	_tiletexture = ResourceManager::getTexture("Game/Textures/tiles.png");
	_symboltexture = ResourceManager::getTexture("Game/Textures/symbols.png");
}

int gridSnap(int i, int snap) {
	if (i % snap > 0)
		return i - (i % snap);
	else return i - snap - (i % snap);
}

void Controller::render(float deltaTime,Camera2D& cam) {
	cam.move(_moveX * speed * deltaTime, _moveY * speed * deltaTime);
	/*if (_CameraScale != 0) {
		cam.scale(_CameraScale, glm::vec2(cam.getWidth() / 2, cam.getHeight() / 2));
		_CameraScale = 0;
	}*/
	glm::vec2 f = cam.screentoWorld(_mouseX,_mouseY);
	_currentTile.x = (float)gridSnap((int)f.x,64);
	_currentTile.y = (float)gridSnap((int)f.y,64);

	if (_specialPlacement && PlacementMode == PLACING)
		_level.setSpawnPoint((int)_currentTile.x, (int)_currentTile.y);
	else
		switch (PlacementMode) {
			case PLACING:
				_level.edit(_currentTile);
				break;
			case DELETING:
				_level.edit(_currentTile,true);
				break;
		}
	
	SpriteRenderer::UseProgram(cam);
	_level.drawSprites(_tiletexture);
	if (PlacementMode != DELETING && !_specialPlacement)SpriteRenderer::drawSprite(_tiletexture, _currentTile.x, _currentTile.y, 64, 64, 0, 8, _currentTile.TileID);
	_level.drawEditorSprites(_symboltexture);
	SpriteRenderer::UnuseProgram();
}
#include <iostream>

void Controller::setMovement(Direction dir,bool s) {
	MovementInputs[dir] = s;

	_moveX = (float)(MovementInputs[LEFT] ? (MovementInputs[RIGHT] ? 0 : -1) : MovementInputs[RIGHT] ? 1 : 0);
	_moveY = (float)(MovementInputs[UP] ? (MovementInputs[DOWN] ? 0 : 1) : MovementInputs[DOWN] ? -1 : 0);
}

void Controller::input(SDL_Event event, int screenh)
{
	SDL_GetMouseState(&_mouseX,&_mouseY);
	_mouseY = screenh - _mouseY;

	if (event.type == SDL_KEYDOWN) {
		std::string path;
		switch (event.key.keysym.sym) {
		case SDLK_w:setMovement(UP,true); break;
		case SDLK_s:setMovement(DOWN, true); break;
		case SDLK_a:setMovement(LEFT, true); break;
		case SDLK_d:setMovement(RIGHT, true); break;

		case SDLK_SPACE:_specialPlacement = !_specialPlacement; break;
		case SDLK_r:_currentTile.TileID--; break;
		case SDLK_t:_currentTile.TileID++; break;

		case SDLK_TAB:
			std::printf("(LOAD) Level name:");
			std::cin >> path;
			_level.load(path.c_str());
			std::printf("Loaded level!\n");
			break;
		case SDLK_RETURN:
			std::printf("(SAVE) Level name:");
			std::cin >> path;
			_level.save(path.c_str());
			std::printf("Saved level!\n");
			break;
		}
	}
	else if (event.type == SDL_KEYUP) {
		switch (event.key.keysym.sym) {
		case SDLK_w:setMovement(UP, false); break;
		case SDLK_s:setMovement(DOWN, false); break;
		case SDLK_a:setMovement(LEFT, false); break;
		case SDLK_d:setMovement(RIGHT, false); break;
		}
	}
	else if (event.type == SDL_MOUSEWHEEL) {
		if (event.wheel.y > 0)
			_CameraScale = 0.1f;
		else if (event.wheel.y < 0)
			_CameraScale = -0.1f;
	}
	else if (event.type == SDL_MOUSEBUTTONDOWN) {
		switch (event.button.button) {
		case SDL_BUTTON_LEFT:
			PlacementMode = PLACING; break;
		case SDL_BUTTON_RIGHT:
			PlacementMode = DELETING; break;
		}
	}
	else if (event.type == SDL_MOUSEBUTTONUP) {
		PlacementMode = NONE;
	}
}