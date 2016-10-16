#pragma once
#include <SDL/SDL.h>
#include <GL/glew.h>
#include <Engine/Timing.h>
#include <Engine/GLSLShading.h>
#include <Engine/Window.h>
#include <Engine/Camera2D.h>
#include <Engine/Text.h>
#include "Player.h"

enum class GameState {PLAY,EXIT};

class Game
{
public:
	Game();
	~Game();

	void run();

private:
	Window _WINDOW;
	GameState _state;
	Timing _frameLimiter;
	GLSLShading _spriteShader, _rShader;
	Player _Player;
	Camera2D _Camera;

	float _time;
	int _Width, _Height;
	bool _isFullscreen;
	void TypeTest(SDL_KeyboardEvent,Text &);
	void init();
	void shaderSetup();
	void loop();
	void render();
	void handleInput();
	void handleKeyboardDownInput(SDL_Event);
	void handleKeyboardUpInput(SDL_Event);
};

