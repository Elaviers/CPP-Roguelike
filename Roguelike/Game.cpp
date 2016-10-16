#include "Game.h"

Game::Game() : _running(true)
{
}

void Game::start() {
	SDL_Init(SDL_INIT_EVERYTHING);
	_window.create("The Window of Hope", 1280, 720, 0);
	loop();
}

void Game::loop() {
	while (_running) {
		handleInput();
	}
}

void Game::handleInput() {
	SDL_Event event;
	if (SDL_PollEvent(&event) == 1)
		if (event.type == SDL_QUIT)
			_running = false;
}