#include "Game.h"
#include <iostream>

Game::Game() : _running(true) {}

void Game::start() {
	SDL_Init(SDL_INIT_EVERYTHING);
	_window.create("The Window of Hope", WIDTH, HEIGHT, 0);
	SDL_GL_SetSwapInterval(0);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_ShowCursor(false);

	std::printf("You're still running OpenGL version %s? What a noob!\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//////////////////init shaders
	_shader.compileShaders("Shaders/sprite.frag", "Shaders/sprite.vert");
	_shader.addAttribute("vertPosition");
	_shader.addAttribute("vertColour");
	_shader.addAttribute("vertUV");
	_shader.linkShaders();

	_shaderlsd.compileShaders("Shaders/DRUGS.frag", "Shaders/DRUGS.vert");
	_shaderlsd.addAttribute("vertPosition");
	_shaderlsd.addAttribute("vertColour");
	_shaderlsd.addAttribute("vertUV");
	_shaderlsd.linkShaders();
	/////////////////

	_camera.init(WIDTH,HEIGHT);
	_player.init(0, 0, 64, "crosshair.png");
	_sprite.init(-1, -1, 2, 2);
	loop();
	}

void Game::loop() {
	int frameNumber = 0;
	while (_running) {
		frameNumber++;

		_frameTimer.begin();
		handleInput();
		_player.updateMousePosition();
		render();
		_frameTimer.end();

		time += _frameTimer.deltaTime;
		//std::printf("TIME:%f     MOUSEPOS:%d|%d\n",time,_player.mouseX,_player.mouseY);
		if (frameNumber % 10 == 0)_window.setTitle("The phsychedelic window of hope, running at a buttery smooth "+std::to_string(_frameTimer.getFramerate())+" frames a second!");
		

	}
}

void Game::render() {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearDepth(1);

	_camera.update();

	_shaderlsd.useProgram();
	GLint shaderTime = _shaderlsd.getUniformLocation("time");
	glUniform1f(shaderTime, time);
	_sprite.render();
	_shaderlsd.unUseProgram();

	_shader.useProgram();
	_player.render(_shader,_camera);
	_shader.unUseProgram();

	_window.swapBuffer();
}

void Game::handleInput() {
	SDL_Event event;
	if (SDL_PollEvent(&event) == 1)
		if (event.type == SDL_QUIT)
			_running = false;
}
