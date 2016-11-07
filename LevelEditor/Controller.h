#pragma once
#include <SDL/SDL.h>
#include <Engine/Sprite.h>
#include <Engine/Camera2D.h>
#include "Level.h"
#include "GUI.h"

namespace PlayerEnums {
	enum EditMode { NONE, PLACING, DELETING };
	enum Direction { RIGHT, UP, LEFT, DOWN };
}

class Controller
{
private:
	Button _loadButton,_saveButton;

	Tile _currentTile;
	Level _level;
	Texture _tiletexture,_symboltexture;

	bool _specialPlacement,_usingUI;

	int _mouseX, _mouseY;
	float _moveX, _moveY, _CameraScale;

	PlayerEnums::EditMode PlacementMode;

	bool MovementInputs[4];
	
	void setMovement(PlayerEnums::Direction,bool);

	static void save(), load();
public:
	static Level* currentLevel;

	float speed;
	Controller() : speed(768) {};

	void init();
	void render(float deltaTime,Camera2D&);
	void input(SDL_Event event,int);
};
