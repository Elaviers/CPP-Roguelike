#pragma once

#include <SDL/SDL.h>
#include <Engine/Window.h>
#include <Engine/Timing.h>
#include <Engine/GLSLShading.h>

class Game {

private:
	Window _window;
	Timing _timing;
	GLSLShading _shader;

	float _width, _height;

public:
	Game();

	void open();
	void createWindow();
	void createShaders();
	void render();
	void getInput();
	void loop();

};