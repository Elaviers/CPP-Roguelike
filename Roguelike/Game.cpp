#include "Game.h"

#include "Constants.h"
#include "FileManager.h"
#include "GameData.h"
#include "GameManager.h"
#include "Menu.h"
#include "Player.h"
#include "UIWindow.h"

#include <bass.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <Engine/ErrorHandling.h>
#include <Engine/GUI.h>
#include <Engine/LineRenderer.h>
#include <Engine/ResourceManager.h>
#include <Engine/SpriteRenderer.h>
#include <SDL/SDL.h>

/////////////////////////////////
Game::Game() : _running(true) {}

inline void log(std::string l) { printf("%s", l.c_str()); }

HSTREAM music, music2;

void Game::stop() {
	_running = false;
}

void Game::start() {
	GameData::gameInstance = this;
	////////

	std::vector<StringPair> properties;
	FileManager::readFile("Game/wololo.zestyconfig",properties);
	GameData::screenDimensions.x = FileManager::readInt(properties,"resx");
	GameData::screenDimensions.y = FileManager::readInt(properties, "resy");

	////////////SDL
	log("Creating window...");

	SDL_Init(SDL_INIT_EVERYTHING);
	_window.create("The Window of Hope", GameData::screenDimensions.x, GameData::screenDimensions.y,(FileManager::readBool(properties,"fullscreen") ? SDL_WINDOW_FULLSCREEN : 0) | SDL_WINDOW_RESIZABLE);
	
	SDL_GL_SetSwapInterval(FileManager::readBool(properties, "vsync"));//vsync
	if (FileManager::readBool(properties, "vsync"))_frameTimer.setFPSCap(60);

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
	ResourceManager::setFontLibrary(FtLib);
	ResourceManager::getFontRef(Constants::font);
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
	//other init
	LineRenderer::init();
	SpriteRenderer::init();

	GlobalUI::setCameraSize(GameData::screenDimensions.x, GameData::screenDimensions.y);

	GameData::camera = new Camera2D();
	GameData::camera->SetViewportSize(GameData::screenDimensions.x, GameData::screenDimensions.y);

	Menu::init();

	_bg.init(-1, -1, 2, 2);

	loop();
}

void Game::beginGame(const char* level) {
	SDL_ShowCursor(SDL_DISABLE);

	////////////init
	
	GameData::level = new Level();
	GameData::level->tileSheet = ResourceManager::getTextureRef("Game/Textures/tiles.png");;
	GameData::level->load(level);

	Vector2 spawn = GameData::level->getSpawnPoint();

	std::printf("Spawn at %d %d\n",spawn.x + 32,spawn.y);

	_player = new Player();
	_player->init(spawn.x + 32, spawn.y, 128, 32, "Game/Textures/crosshair.png", "Game/Textures/player.png");
	GameManager::addEntity(_player);

	log("Game started\n");
	//////////////////
}

void Game::loop() {
	int frameNumber = 0;
	while (_running) {
		_frameTimer.begin();

		frameNumber++;
		GameData::runTime += _frameTimer.deltaTime;

		handleInput();
		GameManager::update();
		render(_frameTimer.deltaTime);

		if (frameNumber % 10 == 0)_window.setTitle("Boring Title (" + std::to_string(_frameTimer.getFramerate()) + " FPS, Time is " + std::to_string(GameData::runTime) + ") (X:" + std::to_string(GameData::mousePosition.x) + " Y:" + std::to_string(GameData::mousePosition.y) + ')');

		_frameTimer.end();
	}

	BASS_Free();
}

void Game::render(float deltaTime) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearDepth(1);

	/////////////////////////////////////////////////
	_shaderlsd.useProgram();
	_shaderlsd.set1f("time", GameData::runTime);
	_bg.render();
	_shaderlsd.unUseProgram();

	////////////////////////////////////////////////
	SpriteRenderer::UseProgram(*GameData::camera);
	GameManager::renderLevel(-2, 0);
	SpriteRenderer::UnuseProgram();

	_shader.useProgram();
	_shader.set1i("sTexture", 0);
	_shader.setMat4("projection", GameData::camera->getCameraMatrix());
	GameManager::renderObjects(_shader, deltaTime);
	_shader.unUseProgram();

	SpriteRenderer::UseProgram(*GameData::camera);
	GameManager::renderLevel(1, 2);
	SpriteRenderer::UnuseProgram();
	////////////////////////////////////////////////
	GlobalUI::render(NULL);

	_fontshader.useProgram();
	_fontshader.set1i("sTexture", 0);
	_fontshader.setMat4("projection", GameData::camera->getScreenMatrix());
	GlobalUI::render(&_fontshader);
	_fontshader.unUseProgram();
	///////////////////////////////////////////////
	LineRenderer::render(*GameData::camera);

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
			if (_player && !GameData::mouseOnGUI)_player->setShooting(true);
			GlobalUI::click();
			break;

		case SDL_MOUSEBUTTONUP:
			if (_player)_player->setShooting(false); break;

		case SDL_MOUSEWHEEL:
			if (event.wheel.y > 0)
				GameData::camera->scale(0.1f);
			else
				GameData::camera->scale(-0.1f);
			break;

		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE) { _running = false; break; }
			if (event.key.keysym.sym == SDLK_i) { GameData::camera->setAngle(GameData::camera->getAngle() + .01f); break; }
			if (event.key.keysym.sym == SDLK_o) { GameData::camera->setAngle(GameData::camera->getAngle() - .01f); break; }
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

			if (_player)_player->keyDown(event); break;

		case SDL_KEYUP:
			if (_player)_player->keyUp(event); break;

		case SDL_WINDOWEVENT:
			if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
				GameData::screenDimensions.x = event.window.data1;
				GameData::screenDimensions.y = event.window.data2;
				glViewport(0,0, GameData::screenDimensions.x, GameData::screenDimensions.y);
				GameData::camera->SetViewportSize(GameData::screenDimensions.x, GameData::screenDimensions.y);
				GlobalUI::setCameraSize(GameData::screenDimensions.x, GameData::screenDimensions.y);			
			}
			break;
		}
}