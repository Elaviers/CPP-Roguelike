#include "Game.h"
#include "Playerr.h"
#include <iostream>



void Playerr::mousestate() {
	
	std::cout << mouseX;
	std::cout << mouseY;

	}

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
