#pragma once
#include <SDL/SDL.h>
#include <Engine/Sprite.h>
#include <Engine/Camera2D.h>
#include "Level.h"

enum EditMode { NONE, PLACING, DELETING };

class Controller
{
private:
	Tile _currentTile;
	Level _level;
	Texture _tiletexture,_symboltexture;

	bool _specialPlacement;

	int _mouseX, _mouseY;
	float _moveX, _moveY, _CameraScale;

	EditMode PlacementMode;

	bool u, d, l, r;
public:

	float speed;
	Controller() : speed(768) {};

	void init();
	void render(float deltaTime,Camera2D&);
	void input(SDL_Event event,int);
};
