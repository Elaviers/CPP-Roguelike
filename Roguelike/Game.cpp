#include "Game.h"
#include "FileManager.h"

#include <Engine/ErrorHandling.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <iostream>

Game::Game() : _running(true) {}

void log(std::string l) { printf("%s", l.c_str()); }

void Game::start() {
	std::vector<StringPair> properties = FileManager::readFile("Game/wololo.zestyconfig");
	ScreenWidth = FileManager::readInt(properties,"resx");
	ScreenHeight = FileManager::readInt(properties, "resy");

	////////////SDL
	log("Creating window...");

	SDL_Init(SDL_INIT_EVERYTHING);
	_window.create("The Window of Hope", ScreenWidth, ScreenHeight,(FileManager::readBool(properties,"fullscreen") ? SDL_WINDOW_FULLSCREEN : 0) | SDL_WINDOW_RESIZABLE);
	SDL_GL_SetSwapInterval(FileManager::readBool(properties, "vsync"));//vsync
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_ShowCursor(false);

	log("done!\n");
	////////////GL
	std::printf("You're still running OpenGL version %s? What a noob!\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	///////////FREETYPE
	log("Loading fonts...");

	FT_Library FtLib;

	if (FT_Init_FreeType(&FtLib))error("Could not initialise FreeType!");
	_font.init(FtLib, "Game/Fonts/arial.ttf", 16);
	FT_Done_FreeType(FtLib);

	log("done!\n");
	////////////init shaders
	log("Compiling shaders...");
	_shader.loadPreset(ShaderPreset::TRANSFORM_SPRITE);
	_shader.link();

	_fontshader.loadPreset(ShaderPreset::FONT);
	_fontshader.link();

	_shaderlsd.compile("Game/Shaders/DRUGS.frag", "Game/Shaders/DRUGS.vert");
	_shaderlsd.addAttribute("vertPosition");
	_shaderlsd.addAttribute("vertColour");
	_shaderlsd.addAttribute("vertUV");
	_shaderlsd.link();
	
	log("done!\n");
	////////////init
	_camera.SetViewportSize(ScreenWidth, ScreenHeight);
	_level.init("Game/lvl.zestylevel");

	SpriteRenderer::init();
	SpawnPoint spawn = _level.getSpawnPoint();
	_camera.setPosition(glm::vec2(spawn.x-ScreenWidth/2,spawn.y-ScreenHeight/2));
	_player.init(spawn.x, spawn.y, 128, 64, "Game/Textures/crosshair.png", "Game/Textures/pointer.png");
	_sprite.init(-1, -1, 2, 2);

	log("Initialised!\n");

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

	/////////////////////////////////////////////////
	_shaderlsd.useProgram();
	_shaderlsd.set1f("time",time);
	_sprite.render();
	_shaderlsd.unUseProgram();
	////////////////////////////////////////////////
	_shader.useProgram();
	_shader.set1i("sTexture",0);
	_shader.setMat4("projection", _camera.getCameraMatrix());

	_level.render(_shader);
	_player.render(_camera,deltaTime,_shader);

	_shader.unUseProgram();
	////////////////////////////////////////////////
	_fontshader.useProgram();
	_fontshader.set1i("sTexture", 0);
	_fontshader.setMat4("projection", _camera.getScreenMatrix());

	_font.drawString("SAMPLE TEXT SAMPLE TEXT SAMPLE TEXT SAMPL3 T3XT", 0, 256, glm::vec4(1,0,1,1), _fontshader);

	_fontshader.unUseProgram();


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

		case SDL_MOUSEWHEEL:
			if (event.wheel.y > 0)
				_camera.scale(0.1f);
			else
				_camera.scale(-0.1f);
			break;

		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE) { _running = false; break; }
			if (event.key.keysym.sym == SDLK_i) { _camera.setAngle(_camera.getAngle() + .1f); break; }
			if (event.key.keysym.sym == SDLK_o) { _camera.setAngle(_camera.getAngle() - .1f); break; }
			if (event.key.keysym.sym == SDLK_f) { SDL_SetWindowFullscreen(_window.GetWindowID(), true); break; }
			_player.keyDown(event); break;

		case SDL_KEYUP:
			_player.keyUp(event); break;

		case SDL_WINDOWEVENT:
			if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
				ScreenWidth = event.window.data1;
				ScreenHeight = event.window.data2;
				glViewport(0,0,ScreenWidth,ScreenHeight);
				_camera.SetViewportSize(ScreenWidth, ScreenHeight);
				_player.setPointerLocation(_camera.getPosition().x + ScreenWidth / 2, _camera.getPosition().y + ScreenHeight / 2);
			}
			break;
		}
}