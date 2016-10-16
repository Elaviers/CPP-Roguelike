#include <iostream>
#include "Game.h"
#include "Player.h"
#include <Engine/Camera2D.h>

Game::Game() : _width(1280), _height(720) {
}

bool running = true;
Player player;
Camera2D cam;

void Game::open() {
	createWindow();
	createShaders();
	cam.init(_width, _height);
	player.init(256,256,256,256);
	loop();
}

void Game::createWindow() {
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	_window.create("Test project",_width,_height,0);

	std::printf("Running on OpenGL %s!\n", glGetString(GL_VERSION));

	glClearColor(.25f,0,0,1);

	SDL_GL_SetSwapInterval(1);
}

void Game::createShaders() {
	_shader.compileShaders("stuff/shaders/sprite.frag", "stuff/shaders/sprite.vert");
	_shader.addAttribute("VertPosition");
	_shader.addAttribute("VertColour");
	_shader.addAttribute("VertUV");
	_shader.linkShaders();
}

void Game::loop() {
	while (running) {
		_timing.begin();
		getInput();
		render();
		_timing.end();
	}
}

void Game::render() {
	glClearDepth(1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_shader.useProgram();
	player.render(_shader,cam,_timing.deltaTime);
	_shader.unUseProgram();

	_window.swapBuffer();

	cam.update();
}

void Game::getInput() {
	SDL_Event action;
	SDL_PollEvent(&action);
}