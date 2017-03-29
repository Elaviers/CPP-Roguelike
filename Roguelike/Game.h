#pragma once

#include <Engine/Window.h>
#include <Engine/Timing.h>
#include <Engine/Shader.h>
#include <Engine/Sprite.h>
#include <Engine/Camera2D.h>
#include <Engine/Font.h>

#include "Player.h"
#include "Level.h"
#include "GameManager.h"

class Game
{
private:
	Window _window;
	Timing _frameTimer;
	bool _running;
	/////////////////////
	Player _player;
	Sprite _sprite;
	Shader _shaderlsd,_shader,_fontshader;
public:
	Game();
	~Game() {};

	void start();
	void stop();
	void loop();

	void beginGame(const char* level);

	void render(float);

	void handleInput();
;
};

