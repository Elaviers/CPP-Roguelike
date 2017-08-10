#pragma once
#include "Controller.h"

#include <Engine/Camera2D.h>
#include <Engine/Timer.h>
#include <Engine/Shader.h>
#include <Engine/Window.h>

class Editor
{
private:
	Window _window;
	bool running;
	int screenX, screenY;

	Timer _frameCounter;
	Camera2D _camera;
	Controller _controller;

	Shader _fontShader;

	void render(float);
public:
	Editor() : running(true), screenX(1024), screenY(768) {};
	~Editor() {};

	void start();
	void windowInput();
};
