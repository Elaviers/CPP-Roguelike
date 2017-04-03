#pragma once
#include <SDL/SDL.h>
#include <Engine/Camera2D.h>
#include "Level.h"
#include <Engine/GUI.h>
#include "FileManager.h"

namespace PlayerEnums {
	enum EditMode { NONE, PLACING_TILE, DELETING_TILE, PLACING_ENT, DELETING_ENT };
	//enum PlacementEmun { TILE, FLAG, SPAWNPOINT };
	enum Direction { RIGHT, UP, LEFT, DOWN };
}

using namespace GUI;

class Controller
{
private:
	UIContainer _menuBar; //Parents MUST be declared before children or they will not be able to destruct properly
	Button _loadButton,_saveButton;
	TextBox _namebox;

	UIText _counter;
	//////////////////////////////////
	static bool _inputLock;
	static const char* levelname;

	Tile _currentTile;
	Level _level;
	Texture _tiletexture,_symboltexture;

	bool _usingUI;

	int _mouseX, _mouseY;
	float _moveX, _moveY, _CameraScale;

	PlayerEnums::EditMode _editMode;
	bool _entMode;
	//PlayerEnums::PlacementEmun _placeMode;

	bool MovementInputs[4];
	
	void setMovement(PlayerEnums::Direction,bool);

	static void save(), load(), setInputState(bool);
public:
	static Level* currentLevel;

	float speed;

	Controller();
	~Controller() {};

	void init();
	void render(float deltaTime,Camera2D&);
	void input(SDL_Event event,int);
};
