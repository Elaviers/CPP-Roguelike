#pragma once

#include <Engine/Window.h>
#include <Engine/Timing.h>
#include <Engine/Camera2D.h>
#include <Engine/LineRenderer.h>
#include <Engine/SpriteRenderer.h>
#include <Engine/Font.h>
#include <SDL/SDL.h>

#include <GL/glew.h>

#include "GUI.h"
#include "Controller.h"

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
	Font _font;

	void render(float);
public:
	Editor() : screenX(1024), screenY(768) {};
	~Editor() {};

	void start();
	void windowInput();
};

