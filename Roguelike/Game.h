#pragma once

#include <SDL/SDL.h>
#include <Engine/Window.h>
#include <Engine/Timing.h>
#include <Engine/Shader.h>
#include <Engine/Sprite.h>
#include <Engine/Camera2D.h>

#include "Player.h"
#include "Level.h"

class Game
{
private:
	Window _window;
	Timing _frameTimer;
	bool _running;
	Camera2D _camera;
	/////////////////////
	Level _level;
	Player _player;
	Sprite _sprite;
	Shader _shaderlsd,_shader,_coolshader;
public:
	float time;
	int ScreenWidth, ScreenHeight;

	Game();

	void start();
	void loop();

	void render(float);

	void handleInput();
;
};

