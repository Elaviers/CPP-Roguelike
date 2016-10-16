#include "Game.h"

Game::Game() : _running(true) {}

void Game::start() {
	SDL_Init(SDL_INIT_EVERYTHING);
	_window.create("The Window of Hope", 1280, 720, 0);

	SDL_GL_SetSwapInterval(0);

	std::printf("You're still running OpenGL version %s? What a noob!\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

	//////////////////init shaders
	_shader.compileShaders("Shaders/DRUGS.frag", "Shaders/DRUGS.vert");
	_shader.addAttribute("vertPosition");
	_shader.addAttribute("vertColour");
	_shader.addAttribute("vertUV");
	_shader.linkShaders();
	/////////////////

	_sprite.init(-1, -1, 2, 2);
	loop();
}

void Game::loop() {
	int frameNumber = 0;
	while (_running) {
		frameNumber++;

		_frameTimer.begin();
		handleInput();
		render();
		time += _frameTimer.deltaTime;
		_frameTimer.end();

		std::printf("%f\n",time);

		if (frameNumber % 10 == 0)_window.setTitle("The phsychedelic window of hope, running at a buttery smooth "+std::to_string(_frameTimer.getFramerate())+" frames a second!");
	}
}

void Game::render() {
	_shader.useProgram();
	GLint shaderTime = _shader.getUniformLocation("time");
	glUniform1f(shaderTime, time);
	_sprite.render();
	_shader.unUseProgram();

	_window.swapBuffer();
}

void Game::handleInput() {
	SDL_Event event;
	if (SDL_PollEvent(&event) == 1)
		if (event.type == SDL_QUIT)
			_running = false;
}