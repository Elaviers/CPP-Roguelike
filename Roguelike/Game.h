#pragma once

#include <SDL/SDL.h>
#include <Engine/Window.h>

class Game
{
private:	
	Window _window;
	bool _running;
public:
	Game();

	void start();
	void loop();
	void handleInput();
};

