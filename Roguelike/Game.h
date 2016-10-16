#pragma once

#include <SDL/SDL.h>
#include <Engine/Window.h>
#include <Engine/Timing.h>
#include <Engine/GLSLShading.h>
#include <Engine/Sprite.h>
#include <Engine/Camera2D.h>

#define WIDTH 1280
#define HEIGHT 720

#include "Player.h"

class Game
{
private:
	Window _window;
	Timing _frameTimer;
	bool _running;
	Camera2D _camera;
	/////////////////////
	Player _player;
	Sprite _sprite;
	GLSLShading _shaderlsd,_shader;
public:
	float time;


	Game();

	void start();
	void loop();

	void render();

	void handleInput();
;
};

