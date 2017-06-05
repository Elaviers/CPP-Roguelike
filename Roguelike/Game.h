#pragma once
#include "Player.h"

#include <Engine/Shader.h>
#include <Engine/Sprite.h>
#include <Engine/Timer.h>
#include <Engine/Window.h>

class Game
{
private:
	Window _window;
	Timer _frameTimer;
	bool _running;
	/////////////////////
	Sprite _bg;
	Shader _shaderlsd,_shader,_fontshader;

	Texture* _tileSheet;

	Player* _player;
public:
	Game();
	~Game() {};

	void start();
	void stop();
	void loop();

	void beginGame(const char* level);

	void update();
	void render();

	void handleInput();
};
