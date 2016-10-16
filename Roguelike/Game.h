#pragma once

#include <SDL/SDL.h>
#include <Engine/Window.h>
#include <Engine/Timing.h>
#include <Engine/GLSLShading.h>
#include <Engine/Sprite.h>

class Game
{
private:	
	Window _window;
	Timing _frameTimer;
	bool _running;

	Sprite _sprite;
	GLSLShading _shader;
public:
	float time;


	Game();

	void start();
	void loop();

	void render();

	void handleInput();
};

