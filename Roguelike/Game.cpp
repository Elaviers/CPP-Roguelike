#include "Game.h"

#include "Constants.h"
#include "FileManager.h"
#include "GameData.h"
#include "Menu.h"
#include "Player.h"
#include "UIWindow.h"
#include "World.h"
#include <Engine/ErrorHandling.h>
#include <Engine/GUI.h>
#include <Engine/LineRenderer.h>
#include <Engine/ResourceManager.h>
#include <Engine/SpriteRenderer.h>
#include <bass.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <GL/glew.h>
#include <GLM/gtc/matrix_transform.hpp>
#include <SDL/SDL.h>

/////////////////////////////////
Game::Game() : _running(true) {}

inline void log(String l) { printf(l.getData()); }

HSTREAM music, music2;

void Game::stop() {
	_running = false;
}

void Game::start() {
	GameData::gameInstance = this;
	////////

	std::vector<StringPair> properties;
	FileManager::readFile("Game/config.cfg", properties);
	GameData::screenDimensions.x = FileManager::readInt(properties, "resx");
	GameData::screenDimensions.y = FileManager::readInt(properties, "resy");

	////////////SDL
	log("Creating window...");

	SDL_Init(SDL_INIT_EVERYTHING);
	_window.create("The Window of Hope", GameData::screenDimensions.x, GameData::screenDimensions.y, (FileManager::readBool(properties, "fullscreen") ? SDL_WINDOW_FULLSCREEN : 0) | SDL_WINDOW_RESIZABLE);

	SDL_GL_SetSwapInterval(FileManager::readBool(properties, "vsync"));//vsync
	int fpscap = FileManager::readInt(properties, "fpslimit");
	if (fpscap > 0)_frameTimer.setFPSCap(fpscap);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	log("done!\n");
	////////////BASS
	log("Initialising BASS...");
	BASS_Init(-1, 44100, 0, 0, NULL);

	music = BASS_StreamCreateFile(FALSE, "Game/Audio/Loop.wav", 0, 0, 0);
	music2 = BASS_StreamCreateFile(FALSE, "Game/Audio/SoundTest.wav", 0, 0, 0);
	BASS_ChannelSetAttribute(music, BASS_ATTRIB_VOL, 0.25f);
	BASS_ChannelFlags(music, BASS_SAMPLE_LOOP, BASS_SAMPLE_LOOP);
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
	Constants::create_registry();
	LineRenderer::init();
	SpriteRenderer::init();
	SpriteRenderer::setUVData(8, Colour()); //render all things with 8 divs

	GlobalUI::setCameraSize(GameData::screenDimensions.x, GameData::screenDimensions.y);

	GameData::camera = new Camera();
	GameData::camera->SetViewportSize(GameData::screenDimensions.x, GameData::screenDimensions.y);



	Menu::init();

	_bg.init(-1, -1, 2, 2);

	loop();
}

void Game::beginGame(const char* level) {
	SDL_ShowCursor(SDL_DISABLE);

	////////////init

	_tileSheet = ResourceManager::getTextureRef("Game/Textures/tiles.png");;
	World::load(level);

	int spawnX = 0, spawnY = 0;
	{
		std::vector<unsigned int> spawnpoints;

		int i = 0;

		for (auto it = World::entities()->begin(); it != World::entities()->end(); it++, i++) {
			if ((*it)->getID() == 0)
				spawnpoints.push_back(i);
		}

		if (spawnpoints.size() > 0) {
			int index = rand() % spawnpoints.size();
			spawnX = (int)(*World::entities())[index]->position.x;
			spawnY = (int)(*World::entities())[index]->position.y;
		}
	}

	std::printf("Spawn at %d %d\n", spawnX + 32, spawnY);

	_player = new Player();
	_player->init(spawnX + 32, spawnY, 128, 32, "Game/Textures/crosshair.png", "Game/Textures/player.png");
	World::addEntity(_player);

	log("Game started\n");
	//////////////////
}

void Game::loop() {
	int frameNumber = 0;
	while (_running) {
		_frameTimer.begin();

		frameNumber++;

		handleInput();
		update();
		render();

		if (frameNumber % 10 == 0)_window.setTitle(
					(	"Boring Title (" + String::convert(_frameTimer.getFramerate()) + 
						" FPS, Time is " + String::convert(GameData::runTime) + 
						") (X:" + String::convert(GameData::mousePosition.x) + 
						" Y:" + String::convert(GameData::mousePosition.y) + ')').getData());

		_frameTimer.end();
	}

	BASS_Free();
}

void Game::update() {
	float deltaTime = _frameTimer.deltaTime * GameData::timeScale;
	GameData::runTime += deltaTime;
	
	SDL_GetMouseState(&GameData::mousePosition.x, &GameData::mousePosition.y);
	GameData::mousePosition.y = GameData::screenDimensions.y - GameData::mousePosition.y;
	GameData::mouseOnGUI = GlobalUI::update(GameData::mousePosition.x, GameData::mousePosition.y);
	
	World::updateEntities(deltaTime);
}

void Game::render() {
	_isomatrix = glm::rotate(GameData::camera->getCameraMatrix(), 0.78539f, glm::vec3(0, 0, 1)); //Z-Rot by 45 degrees
	_isomatrix[1][1] *= cosf(0.61547f);		//X-Rot by arcsin(30 degrees)

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearDepth(1);

	/////////////////////////////////////////////////
	_shaderlsd.useProgram();
	_shaderlsd.set1f("time", GameData::runTime);
	_bg.render();
	_shaderlsd.unUseProgram();

	static Rect_i cameradims;
	cameradims = Rect_i(GameData::camera->getMin(),GameData::camera->getMax());

	////////////////////////////////////////////////
	SpriteRenderer::UseProgram(_isomatrix);
	World::drawTiles(0, true, cameradims, *_tileSheet);
	SpriteRenderer::UnuseProgram();

	_shader.useProgram();
	_shader.set1i("sTexture", 0);
	_shader.setMat4("projection", GameData::camera->getCameraMatrix());
	World::drawEntities(_shader);
	_shader.unUseProgram();

	SpriteRenderer::UseProgram(_isomatrix);
	World::drawTiles(127, false, cameradims, *_tileSheet);
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
	while (SDL_PollEvent(&event))
		switch (event.type) {
		case SDL_TEXTINPUT:

			break;

		case SDL_QUIT:
			_running = false;
			break;

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
					BASS_ChannelPlay(music2, false);
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
				glViewport(0, 0, GameData::screenDimensions.x, GameData::screenDimensions.y);
				GameData::camera->SetViewportSize(GameData::screenDimensions.x, GameData::screenDimensions.y);
				GlobalUI::setCameraSize(GameData::screenDimensions.x, GameData::screenDimensions.y);
			}
			break;
		}
}
