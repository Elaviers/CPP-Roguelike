#include "Game.h"
#include "FileManager.h"

#include <Engine/ErrorHandling.h>
#include <ft2build.h>
#include FT_FREETYPE_H

#include <iostream>
using namespace FileManager;

Game::Game() : _running(true) {}

void Game::start() {
	std::vector<StringPair> properties = readFile("Game/wololo.zestyconfig");

	ScreenWidth = readInt(properties,"resx");
	ScreenHeight = readInt(properties, "resy");

	////////////SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	_window.create("The Window of Hope", ScreenWidth, ScreenHeight,readBool(properties,"fullscreen") ? FULLSCREEN : 0);
	SDL_GL_SetSwapInterval(readBool(properties, "vsync"));//vsync
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_ShowCursor(false);

	////////////GL
	std::printf("You're still running OpenGL version %s? What a noob!\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glClearColor(0,0,0,1);

	///////////FREETYPE
	FT_Library FtLib;
	FT_Face face;

	if (FT_Init_FreeType(&FtLib))error("Could not initialise FreeType!");
	if (FT_New_Face(FtLib, "Game/Fonts/font.ttf", 0, &face))error("I could load a font, noooooooob\a\a\a\a!!!");

	////////////init shaders
	_shader.compile("Game/Shaders/sprite.frag", "Game/Shaders/sprite.vert");
	_shader.addAttribute("vertPosition");
	_shader.addAttribute("vertColour");
	_shader.addAttribute("vertUV");
	_shader.link();

	_shaderlsd.compile("Game/Shaders/DRUGS.frag", "Game/Shaders/DRUGS.vert");
	_shaderlsd.addAttribute("vertPosition");
	_shaderlsd.addAttribute("vertColour");
	_shaderlsd.addAttribute("vertUV");
	_shaderlsd.link();

	_coolshader.compile("Game/Shaders/SpecialSprite.frag","Game/Shaders/SpecialSprite.vert");
	_coolshader.addAttribute("vertPosition");
	_coolshader.addAttribute("vertColour");
	_coolshader.addAttribute("vertUV");
	_coolshader.link();

	////////////init
	_camera.init(ScreenWidth, ScreenHeight);
	_level.init("Game/lvl.zestylevel");
	SpawnPoint spawn = _level.getSpawnPoint();

	_camera.setPosition(glm::vec2(spawn.x-ScreenWidth/2,spawn.y-ScreenHeight/2));
	_player.init(spawn.x, spawn.y, 128, 64, "Game/Top Quality Textures/crosshair.png", "Game/Top Quality Textures/pointer.png");
	_sprite.init(-1, -1, 2, 2);
	loop();
	}

void Game::loop() {
	int frameNumber = 0;
	while (_running) {
		frameNumber++;

		_frameTimer.begin();
		handleInput();
		_player.update(time,(float)ScreenHeight);
		render(_frameTimer.deltaTime);
		_frameTimer.end();

		time += _frameTimer.deltaTime;
		if (frameNumber % 10 == 0)_window.setTitle("The politically correct window of promise, running at an eye popping "+std::to_string(_frameTimer.getFramerate())+" frames a second! "+std::to_string(time));
	}
}

void Game::render(float deltaTime) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearDepth(1);

	_camera.update();

	/////////////////////////////////////////////////
	_shaderlsd.useProgram();
	_shaderlsd.set1f("time",time);
	_sprite.render();
	_shaderlsd.unUseProgram();
	/////////////////////////////////////////////////
	_coolshader.useProgram();
	_coolshader.set1i("sTexture", 0);
	_coolshader.setMat4("p", _camera.getCameraMatrix());
	_level.render(_coolshader);

	_coolshader.unUseProgram();
	////////////////////////////////////////////////
	_shader.useProgram();
	_shader.set1i("sTexture",0);
	_shader.setMat4("p", _camera.getCameraMatrix());

	_player.render(_camera,deltaTime);

	_shader.unUseProgram();
	////////////////////////////////////////////////


	_window.swapBuffer();
}

void Game::handleInput() {
	SDL_Event event;
	if (SDL_PollEvent(&event) == 1)
		switch (event.type) {
		case SDL_QUIT:
			_running = false;
		case SDL_MOUSEBUTTONDOWN:
			_player.setShooting(true); break;
		case SDL_MOUSEBUTTONUP:
			_player.setShooting(false); break;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE) { _running = false; break; }
			if (event.key.keysym.sym == SDLK_i) { _camera.setAngle(_camera.getAngle() + .1f); break; }
			if (event.key.keysym.sym == SDLK_o) { _camera.setAngle(_camera.getAngle() - .1f); break; }
			if (event.key.keysym.sym == SDLK_f) { SDL_SetWindowFullscreen(_window.GetWindowID(),true); break; }
			_player.keyDown(event); break;
		case SDL_KEYUP:
			_player.keyUp(event); break;
		}
}