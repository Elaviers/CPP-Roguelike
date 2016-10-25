#pragma once

#include <Engine/Window.h>
#include <Engine/Timing.h>
#include <Engine/Camera2D.h>
#include <Engine/LineRenderer.h>
#include <SDL/SDL.h>

#include <GL/glew.h>

#include "Controller.h"

class Editor
{
private:
	Window _window;
	bool running;
	int screenX, screenY;

	Shader _shader,_lineshader;
	Timing _frameCounter;
	Camera2D _camera;
	Controller _controller;

	void render(float);
public:
	Editor() : screenX(1280), screenY(720) {};
	~Editor() {};

	void start();
	void windowInput();
};

