#include "Game.h"
#include "FileManager.h"
#include "Menu.h"

#include <bass.h>
#include <SDL/SDL.h>
#include <Engine/ErrorHandling.h>
#include <Engine/ResourceManager.h>
#include <Engine/SpriteRenderer.h>
#include <Engine/GUI.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <iostream>

Game::Game() : _running(true) {}

void log(std::string l) { printf("%s", l.c_str()); }

HSTREAM music, music2;

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
	SDL_ShowCursor(SDL_DISABLE);

	log("done!\n");
	////////////BASS
	log("Initialising BASS...");
	BASS_Init(-1, 44100, 0, 0, NULL);

	music = BASS_StreamCreateFile(FALSE, "Game/Audio/Loop.wav", 0, 0, 0);
	music2 = BASS_StreamCreateFile(FALSE, "Game/Audio/SoundTest.wav", 0, 0, 0);
	BASS_ChannelSetAttribute(music,BASS_ATTRIB_VOL,0.25f);
	BASS_ChannelFlags(music,BASS_SAMPLE_LOOP,BASS_SAMPLE_LOOP);
	BASS_ChannelSetAttribute(music2, BASS_ATTRIB_VOL, 0.5f);
	BASS_ChannelFlags(music2, BASS_SAMPLE_LOOP, BASS_SAMPLE_LOOP);
	BASS_ChannelPlay(music, FALSE);
	log("done!\n");
	////////////GL
	std::printf("You're still running OpenGL version %s? What a noob!\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	///////////FREETYPE
	log("Loading fonts...");

	FT_Library FtLib;
	if (FT_Init_FreeType(&FtLib))error("Could not initialise FreeType!");
	_font.init(FtLib, "Game/Fonts/corbelz.ttf", 32);
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
	SpriteRenderer::init();
	_camera.SetViewportSize(ScreenWidth, ScreenHeight);

	GlobalUI::setCameraSize(ScreenWidth, ScreenHeight);
	//Menu::init(_font);

	Texture tiles = ResourceManager::getTexture("Game/Textures/tiles.png");
	_level.tileSheet = &tiles;
	//_level.load("Game/lvl.zestylevel");
	_level.load("Game/collision.test");

	Vector2 spawn = _level.getSpawnPoint();
	_camera.setPosition(spawn.x-ScreenWidth/2,spawn.y-ScreenHeight/2);
	_player.init((int)spawn.x, (int)spawn.y, 128, 64, "Game/Textures/crosshair.png", "Game/Textures/player.png");
	_player.setLevel(_level);
	_sprite.init(-1, -1, 2, 2);

	log("Initialised!\n");

	loop();
	}

void Game::loop() {
	int frameNumber = 0;
	while (_running) {
		_frameTimer.begin();

		frameNumber++;
		time += _frameTimer.deltaTime;

		if (frameNumber % 10 == 0)_window.setTitle("Boring Title (" + std::to_string(_frameTimer.getFramerate()) + " FPS, Time is " + std::to_string(time) + ')');
		
		handleInput();
		_player.update(time,(float)ScreenHeight);
		render(_frameTimer.deltaTime);

		_frameTimer.end();
	}

	BASS_Free();
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

	_level.drawSprites(_camera,-1);
	_level.drawSprites(_camera,0);
	_player.render(_camera,deltaTime,_shader);

	_shader.unUseProgram();
	////////////////////////////////////////////////
	GlobalUI::render(_fontshader);

	_fontshader.useProgram();
	_fontshader.set1i("sTexture", 0);
	_fontshader.setMat4("projection", _camera.getScreenMatrix());

	const static float f = 4;
	_font.drawString("ROGUELIKE v0.0.1 - now with sound! Press M to change streams!", 0, 0,
		glm::vec4(std::sin(time*f) / 2 + 1,std::sin(time*f + M_PI) / 2 + 1,std::sin(time*f + M_PI * 2) / 2 + 1,1),_fontshader);//haha

	GlobalUI::render(_fontshader);

	_fontshader.unUseProgram();
	///////////////////////////////////////////////

	_window.swapBuffer();
}

void Game::handleInput() {
	static SDL_Event event;
	if (SDL_PollEvent(&event) == 1)
		switch (event.type) {
		case SDL_TEXTINPUT:

			break;

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
			if (event.key.keysym.sym == SDLK_i) { _camera.setAngle(_camera.getAngle() + .01f); break; }
			if (event.key.keysym.sym == SDLK_o) { _camera.setAngle(_camera.getAngle() - .01f); break; }
			if (event.key.keysym.sym == SDLK_f) { SDL_SetWindowFullscreen(_window.GetWindowID(), true); break; }
			if (event.key.keysym.sym == SDLK_m) {
				static bool toggletest = true; if (toggletest) {
					BASS_ChannelPlay(music2,false);
					BASS_ChannelPause(music);
				}
				else {
					BASS_ChannelPlay(music, false);
					BASS_ChannelPause(music2);
				}
				toggletest = !toggletest;
			};

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