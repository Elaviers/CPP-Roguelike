#pragma once
#include "Controller.h"

#include <Engine/Camera2D.h>
#include <Engine/Timing.h>
#include <Engine/Window.h>

class Editor
{
private:
	Window _window;
	bool running;
	int screenX, screenY;

	Timing _frameCounter;
	Camera2D _camera;
	Controller _controller;

	Shader _fontShader;

	void render(float);
public:
	Editor() : screenX(1024), screenY(768) {};
	~Editor() {};

	void start();
	void windowInput();
};
