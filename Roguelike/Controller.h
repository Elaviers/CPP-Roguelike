#pragma once
#include <SDL/SDL.h>
#include <Engine/Camera2D.h>
#include "Level.h"
#include <Engine/GUI.h>
#include "FileManager.h"

namespace PlayerEnums {
	enum EditMode { NONE, PLACING, DELETING };
	enum Direction { RIGHT, UP, LEFT, DOWN };
}

using namespace GUI;

class Controller
{
private:
	Button _loadButton,_saveButton;
	TextBox _namebox;
	UIRoot _root;

	static bool _inputLock;
	static const char* levelname;

	Tile _currentTile;
	Level _level;
	Texture _tiletexture,_symboltexture;

	bool _specialPlacement,_usingUI;

	int _mouseX, _mouseY;
	float _moveX, _moveY, _CameraScale;

	PlayerEnums::EditMode PlacementMode;

	bool MovementInputs[4];
	
	void setMovement(PlayerEnums::Direction,bool);

	static void save(), load(), setInputState(bool);
public:
	static Level* currentLevel;

	float speed;
	Controller();

	void init();
	void render(float deltaTime,Camera2D&);
	void input(SDL_Event event,int);
};
