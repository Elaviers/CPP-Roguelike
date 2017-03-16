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

void Game::stop() {
	_running = false;
}

void Game::start() {
	GameManager::gameInstance = this;
	////////

	std::vector<StringPair> properties = FileManager::readFile("Game/wololo.zestyconfig");
	GameManager::screenDimensions.x = FileManager::readInt(properties,"resx");
	GameManager::screenDimensions.y = FileManager::readInt(properties, "resy");

	GameManager::screenDimensions = Vector2{640,480};

	////////////SDL
	log("Creating window...");

	SDL_Init(SDL_INIT_EVERYTHING);
	_window.create("The Window of Hope", GameManager::screenDimensions.x, GameManager::screenDimensions.y,(FileManager::readBool(properties,"fullscreen") ? SDL_WINDOW_FULLSCREEN : 0) | SDL_WINDOW_RESIZABLE);
	SDL_GL_SetSwapInterval(FileManager::readBool(properties, "vsync"));//vsync
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

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
	//BASS_ChannelPlay(music, FALSE);
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

	GlobalUI::setCameraSize(GameManager::screenDimensions.x, GameManager::screenDimensions.y);

	GameManager::camera = new Camera2D();
	GameManager::camera->SetViewportSize(GameManager::screenDimensions.x, GameManager::screenDimensions.y);

	Menu::init(_font);

	_sprite.init(-1, -1, 2, 2);

	loop();
}

void Game::beginGame() {
	SDL_ShowCursor(SDL_DISABLE);

	////////////init
	SpriteRenderer::init();

	GameManager::level = new Level();
	GameManager::level->tileSheet = ResourceManager::getTextureRef("Game/Textures/tiles.png");;
	GameManager::level->load("Game/collision.test");

	Vector2f spawn = GameManager::level->getSpawnPoint();

	//GameManager::camera->setPosition(spawn.x - GameManager::screenDimensions.x / 2, spawn.y - GameManager::screenDimensions.y / 2);

	_player.init((int)spawn.x, (int)spawn.y, 128, 64, "Game/Textures/crosshair.png", "Game/Textures/player.png");
	GameManager::addObject(&_player);

	//GameManager::camera->

	log("Game started\n");
	//////////////////
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++)
			std::cout << GameManager::camera->getScreenMatrix()[i][j] << " ";
		std::cout << std::endl;
	}
}

void Game::loop() {
	int frameNumber = 0;
	while (_running) {
		_frameTimer.begin();

		frameNumber++;
		GameManager::runTime += _frameTimer.deltaTime;

		handleInput();
		GameManager::update();
		render(_frameTimer.deltaTime);

		if (frameNumber % 10 == 0)_window.setTitle("Boring Title (" + std::to_string(_frameTimer.getFramerate()) + " FPS, Time is " + std::to_string(GameManager::runTime) + ") (X:" + std::to_string(GameManager::mousePosition.x) + " Y:" + std::to_string(GameManager::mousePosition.y) + ')');

		_frameTimer.end();
	}

	BASS_Free();
}

void Game::render(float deltaTime) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearDepth(1);

	/////////////////////////////////////////////////
	_shaderlsd.useProgram();
	_shaderlsd.set1f("time",GameManager::runTime);
	_sprite.render();
	_shaderlsd.unUseProgram();

	////////////////////////////////////////////////
	_shader.useProgram();
	_shader.set1i("sTexture", 0);
	_shader.setMat4("projection", GameManager::camera->getCameraMatrix());

	GameManager::renderLevel(-2, 2);
	GameManager::renderObjects(_shader, deltaTime);

	_shader.unUseProgram();
	////////////////////////////////////////////////
	GlobalUI::render(NULL);

	_fontshader.useProgram();
	_fontshader.set1i("sTexture", 0);
	_fontshader.setMat4("projection", GameManager::camera->getScreenMatrix());

	GlobalUI::render(&_fontshader);

	const static float f = 4;
	_font.drawString("ROGUELIKE v0.0.1 - now with sound! Press M to change streams!", 0, 0,
		glm::vec4(std::sin(GameManager::runTime * f) / 2 + 1, std::sin(GameManager::runTime * f + M_PI) / 2 + 1, std::sin(GameManager::runTime * f + M_PI * 2) / 2 + 1, 1), _fontshader);//haha

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
			if (!GameManager::mouseOnGUI)_player.setShooting(true); 
			GlobalUI::click();
			break;

		case SDL_MOUSEBUTTONUP:
			_player.setShooting(false); break;

		case SDL_MOUSEWHEEL:
			if (event.wheel.y > 0)
				GameManager::camera->scale(0.1f);
			else
				GameManager::camera->scale(-0.1f);
			break;

		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE) { _running = false; break; }
			if (event.key.keysym.sym == SDLK_i) { GameManager::camera->setAngle(GameManager::camera->getAngle() + .01f); break; }
			if (event.key.keysym.sym == SDLK_o) { GameManager::camera->setAngle(GameManager::camera->getAngle() - .01f); break; }
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
				GameManager::screenDimensions.x = event.window.data1;
				GameManager::screenDimensions.y = event.window.data2;
				glViewport(0,0, GameManager::screenDimensions.x, GameManager::screenDimensions.y);
				GameManager::camera->SetViewportSize(GameManager::screenDimensions.x, GameManager::screenDimensions.y);
				GlobalUI::setCameraSize(GameManager::screenDimensions.x, GameManager::screenDimensions.y);			}
			break;
		}
}