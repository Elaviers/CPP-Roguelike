#pragma once
#include <SDL/SDL.h>
#include <Engine/Sprite.h>
#include <Engine/Camera2D.h>

class Controller
{
private:
	Sprite _sprite;
	int _mouseX, _mouseY;
	float _moveX, _moveY, _CameraScale;
public:
	float speed;
	Controller() : speed(768) {};

	void init();
	void render(float deltaTime,Camera2D&);
	void input(SDL_Event event,int);
};
