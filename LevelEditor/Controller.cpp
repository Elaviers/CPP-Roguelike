#include "Controller.h"

#include <Engine/SpriteRenderer.h>
#include <Engine/ResourceManager.h>
#include <iostream>

Level* Controller::currentLevel;
bool Controller::_inputLock;
const char* Controller::levelname;

using namespace PlayerEnums;

void Controller::save() {
	/*std::string path;
	std::printf("(SAVE) Level name:");
	std::cin >> path;
	currentLevel->save(path.c_str());
	std::printf("Saved level!\n");*/
	currentLevel->save(levelname);
}

void Controller::load() {
	/*std::string path;
	std::printf("(LOAD) Level name:");
	std::cin >> path;
	currentLevel->load(path.c_str());
	std::printf("Loaded level!\n");*/
	currentLevel->load(levelname);
}

void Controller::setInputState(bool typing) {
	if (typing) SDL_StartTextInput();
	else SDL_StopTextInput();

	_inputLock = typing;
}

void Controller::init() {
	_namebox = TextBox(0, -32, .5f, 32, NORMALISED_WIDTH);
	_namebox.setAnchor(Anchor::TOP_LEFT);
	_namebox.colour.set(0, 0, 1);
	_namebox.colour2.set(.5f, .5f, .75f);
	_namebox.textColour.set(1, 1, 1);
	_namebox.onStateChanged = &setInputState;

	_loadButton = Button(.5f, -32, .25, 32, NORMALISED_X | NORMALISED_WIDTH);
	_loadButton.setAnchor(Anchor::TOP_LEFT);
	_loadButton.colour.set(1, 1, 0);
	_loadButton.hoverColour.set(1, 0, 0);
	_loadButton.textColour.set(0,0,0);
	_loadButton.label = "Load";
	_loadButton.onClick = &load;

	_saveButton = Button(.75f, -32, .25f, 32, NORMALISED_X | NORMALISED_WIDTH);
	_saveButton.setAnchor(Anchor::TOP_LEFT);
	_saveButton.colour.set(1, 1, 0);
	_saveButton.hoverColour.set(1, 0, 0);
	_saveButton.textColour.set(0, 0, 0);
	_saveButton.label = "Save";
	_saveButton.onClick = &save;

	GUI::add(_namebox);
	GUI::add(_loadButton);
	GUI::add(_saveButton);

	_tiletexture = ResourceManager::getTexture("Game/Textures/tiles.png");
	_symboltexture = ResourceManager::getTexture("Game/Textures/symbols.png");

	currentLevel = &_level;
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
	_level.drawSprites(_tiletexture,cam);
	if (PlacementMode != DELETING && !_specialPlacement && !_usingUI)SpriteRenderer::drawSprite(_tiletexture, _currentTile.x, _currentTile.y, 64, 64, Colour(255,255,255,128), 0, 8, _currentTile.TileID);
	_level.drawEditorSprites(_symboltexture);
	SpriteRenderer::UnuseProgram();
}

void Controller::setMovement(Direction dir,bool s) {
	MovementInputs[dir] = s;

	_moveX = (float)(MovementInputs[LEFT] ? (MovementInputs[RIGHT] ? 0 : -1) : MovementInputs[RIGHT] ? 1 : 0);
	_moveY = (float)(MovementInputs[UP] ? (MovementInputs[DOWN] ? 0 : 1) : MovementInputs[DOWN] ? -1 : 0);
}

void Controller::input(SDL_Event event, int screenh)
{
	SDL_GetMouseState(&_mouseX,&_mouseY);
	_mouseY = screenh - _mouseY;

	_usingUI = GUI::update(_mouseX, _mouseY);

	if (event.type == SDL_TEXTINPUT) {
		_namebox.textInput(event.text.text[0]);
		levelname = _namebox.text.c_str();
	}

	if (event.type == SDL_MOUSEBUTTONDOWN) {
		if (!_usingUI)
			switch (event.button.button) {
			case SDL_BUTTON_LEFT:
				PlacementMode = PLACING; break;
			case SDL_BUTTON_RIGHT:
				PlacementMode = DELETING; break;
			}
		GUI::click();
	}
	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_BACKSPACE && _namebox.text.length() > 0) {
		_namebox.text.pop_back();
	}

	if (_inputLock)return;

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
	else if (event.type == SDL_MOUSEBUTTONUP) {
		PlacementMode = NONE;
	}
}