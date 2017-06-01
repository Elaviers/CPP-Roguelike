#include "Controller.h"

#include "Constants.h"
#include "EntityRegistry.h"

#include <Engine/GUI.h>
#include <Engine/LineRenderer.h>
#include <Engine/ResourceManager.h>
#include <Engine/SpriteRenderer.h>
#include <iostream>

Level* Controller::currentLevel;
bool Controller::_inputLock;
const char* Controller::levelname = "sample.lvl";

using namespace PlayerEnums;

Controller::Controller() :
	speed(768),
	_menuBar(0, 0, 1, -32, NORMALISED_WIDTH | FLIPPED_Y),
	_namebox(0, 0, 1 / 3.0f, 1, NORMALISED_WIDTH | NORMALISED_HEIGHT),
	_loadButton(1 / 3.0f, 0, 1 / 3.0f, 1, NORMALISED_X | NORMALISED_WIDTH | NORMALISED_HEIGHT),
	_saveButton(2 / 3.0f, 0, 1 / 3.0f, 1, NORMALISED_X | NORMALISED_WIDTH | NORMALISED_HEIGHT),
	_counter(0, 0, 1, 32, NORMALISED_WIDTH)
{}

void Controller::save() {
	if (levelname != nullptr) {
		std::cout << "Saving \"" << levelname << "\"...\n";
		currentLevel->save(levelname);
	}
}

void Controller::load() {
	if (levelname != nullptr) {
		std::cout << "Loading \"" << levelname << "\"...\n";
		currentLevel->load(levelname);
	}
}

void Controller::setInputState(bool typing) {
	if (typing) SDL_StartTextInput();
	else SDL_StopTextInput();

	_inputLock = typing;
}

void Controller::init() {
	_namebox.label = "Sample.lvl";
	_namebox.setColour(NormalisedColour(0, 0, 1));
	_namebox.setSelectColour(NormalisedColour(0, 0, 0.5));
	_namebox.label.setColour(NormalisedColour(1, 1, 1, 1));
	_namebox.onStateChanged = setInputState;

	_loadButton.label = "LOAD";
	_loadButton.label.setColour(NormalisedColour(0, 0, 0, 1));
	_loadButton.setColour(NormalisedColour(1, 1, 0));
	_loadButton.setHoverColour(NormalisedColour(1, 0, 0));
	_loadButton.bind_onClick(load);

	_saveButton.label = "SAVE";
	_saveButton.label.setColour(NormalisedColour(0, 0, 0, 1));
	_saveButton.setColour(NormalisedColour(1, 1, 0));
	_saveButton.setHoverColour(NormalisedColour(1, 0, 0));
	_saveButton.bind_onClick(save);

	_counter = "TileID : 0|Layer : 0";
	_counter.setColour(NormalisedColour(1, 1, 1, 1));

	_namebox.label.setFont(Constants::font_editor);
	_saveButton.label.setFont(Constants::font_editor);
	_loadButton.label.setFont(Constants::font_editor);
	_counter.setFont(Constants::font_editor);

	GlobalUI::add(_counter);
	GlobalUI::add(_menuBar);
	_menuBar.addElement(_namebox);
	_menuBar.addElement(_loadButton);
	_menuBar.addElement(_saveButton);
	/////////////////////////////////
	_tiletexture = ResourceManager::getTexture("Game/Textures/tiles.png");
	_symboltexture = ResourceManager::getTexture("Game/Textures/symbols.png");

	currentLevel = &_level;
}

inline int gridSnap(int i, int snap) {
	if (i % snap > 0)
		return i - (i % snap);
	else return i - snap - (i % snap);
}

void Controller::render(float deltaTime, Camera2D& cam) {
	cam.move(_moveX * speed * deltaTime, _moveY * speed * deltaTime);

	Vector2f f = cam.screentoWorld(_mouseX, _mouseY);
	_selection.x = gridSnap((int)f.x, 64);
	_selection.y = gridSnap((int)f.y, 64);

	switch (_editMode) {
	case PLACE:
		if (_entMode) {
			Entity* ent = EntityRegistry::createEntity(_selection.id);
			if (!ent) break;
			ent->position = Vector2f((float)_selection.x,(float)_selection.y);
			_level.addEntity(ent);
		}
		else
			_level.addTile(Tile{ _selection.layer, _selection.id, (signed char)(_selection.x / 64), (signed char)(_selection.y / 64) });
		break;
	case DELETE:
		if (_entMode)
			_level.removeEntity(Vector2f((float)(_selection.x / 64), (float)(_selection.y / 64)));
		else
			_level.removeTile(_selection.layer, (signed char)(_selection.x / 64), (signed char)(_selection.y / 64));
		break;
	}

	SpriteRenderer::UseProgram(cam);

	Rect_i cameraDimensions(cam.getMin(), cam.getMax());
	SpriteRenderer::setUVData(8, Colour(255,255,255,255));
	_level.drawTiles(_selection.layer - 1,	true ,cameraDimensions, _tiletexture);
	SpriteRenderer::setUVData(8, Colour(127, 255, 127, 255));
	_level.drawTiles(_selection.layer,		false, cameraDimensions, _tiletexture);
	SpriteRenderer::setUVData(8, Colour(255, 255, 255, 64));
	_level.drawTiles(127,					false, cameraDimensions, _tiletexture);

	_level.drawEntities(SpriteRenderer::GetShader());

	if (!_usingUI)
		if (!_entMode && _editMode != DELETE) {
			SpriteRenderer::setUVData(8, Colour(255, 255, 255, 127));
			SpriteRenderer::drawSprite(_tiletexture, (float)_selection.x, (float)_selection.y, 64.f, 64.f, 0.0f, _selection.id);
		}
		/*else if (_entMode && _editMode != DELETE) {
			SpriteRenderer::setUVData(4, Colour(255, 255, 255, 127));
			SpriteRenderer::drawSprite(_symboltexture, (float)_selection.x, (float)_selection.y, 64.f, 64.f, 0.0f, _selection.id);
		}*/

	SpriteRenderer::UnuseProgram();

	LineRenderer::render(cam);
}

void Controller::setMovement(Direction dir, bool s) {
	MovementInputs[dir] = s;

	_moveX = (float)(MovementInputs[LEFT] ? (MovementInputs[RIGHT] ? 0 : -1) : MovementInputs[RIGHT] ? 1 : 0);
	_moveY = (float)(MovementInputs[UP] ? (MovementInputs[DOWN] ? 0 : 1) : MovementInputs[DOWN] ? -1 : 0);
}

void Controller::input(SDL_Event event, int screenh)
{
	SDL_GetMouseState(&_mouseX, &_mouseY);
	_mouseY = screenh - _mouseY;

	_usingUI = GlobalUI::update(_mouseX, _mouseY);

	if (event.type == SDL_TEXTINPUT) {
		_namebox.textInput(event.text.text[0]);
		levelname = _namebox.label.getText().c_str();
	}
	else if (event.type == SDL_MOUSEBUTTONDOWN) {
		if (!_usingUI)
			switch (event.button.button) {
			case SDL_BUTTON_LEFT:
				_editMode = PLACE;
				break;
			case SDL_BUTTON_RIGHT:
				_editMode = DELETE; break;
			}
		GlobalUI::click();
	}
	else if (event.type == SDL_MOUSEBUTTONUP) {
		_editMode = NONE;
	}
	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_BACKSPACE && _namebox.label.getText().length() > 0) {
		_namebox.label.pop();
	}

	if (_inputLock)return;

	if (event.type == SDL_KEYDOWN) {
		std::string path;
		switch (event.key.keysym.sym) {
		case SDLK_w:setMovement(UP, true); break;
		case SDLK_s:setMovement(DOWN, true); break;
		case SDLK_a:setMovement(LEFT, true); break;
		case SDLK_d:setMovement(RIGHT, true); break;

		case SDLK_SPACE: _entMode = !_entMode; break;

		case SDLK_r:_selection.id--; break;
		case SDLK_t:_selection.id++; break;
		case SDLK_LEFTBRACKET:_selection.layer--; break;
		case SDLK_RIGHTBRACKET:_selection.layer++; break;
		}

		if (_entMode) {
			_counter = "EntID : " + std::to_string(_selection.id) + " (" + EntityRegistry::getNameOfID(_selection.id) +")";
		}
		else
			_counter = "TileID : " + std::to_string(_selection.id) + "|Layer : " + std::to_string(_selection.layer);
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
}
