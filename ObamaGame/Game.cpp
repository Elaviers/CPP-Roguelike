#include <Engine/ErrorHandling.h>
#include <Engine/Text.h>
#include "Game.h"
#include "Player.h"

Game::Game() : _Width(1280), _Height(720), _time(0)
{
}


Game::~Game()
{
}

Text txt;
Sprite bg;
SpriteBatch testBatch;

void Game::run() {
	init();
	//_frameLimiter.init(60);
	_Player.init((float)_Width / 2 - 128,(float)_Height/2-128);
	bg.init(-1, -1, 2, 2);
	txt.init(0,0,"resource/textures/font.png",64);
	txt = "Type here m8!";
	testBatch.init();

	_Camera.init(_Width,_Height);
	loop();
}

void Game::init() {
	SDL_Init(SDL_INIT_EVERYTHING);
	_state = GameState::PLAY;

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	_WINDOW.create("Obama game",_Width,_Height,0);

	std::printf("   --- Current OpenGL version is %s ---\n",glGetString(GL_VERSION));

	glClearColor(0,0,.1f,1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

	SDL_GL_SetSwapInterval(1);

	shaderSetup();
}

void Game::shaderSetup() {
	_spriteShader.compileShaders("resource/shaders/sprite.frag", "resource/shaders/sprite.vert");
	_spriteShader.addAttribute("vertPosition");
	_spriteShader.addAttribute("vertColour");
	_spriteShader.addAttribute("vertUV");
	_spriteShader.linkShaders();

	_rShader.compileShaders("resource/shaders/spritelsd.frag", "resource/shaders/spritelsd.vert");
	_rShader.addAttribute("vertPosition");
	_rShader.addAttribute("vertColour");
	_rShader.addAttribute("vertUV");
	_rShader.linkShaders();
}

void Game::loop() {
	while (_state != GameState::EXIT) {
		_frameLimiter.begin();

		handleInput();
		render();
		_time += _frameLimiter.deltaTime;

		_Camera.update();

		static int frameCounter = 0;
		frameCounter++;

		if (frameCounter % 10 == 0)
			_WINDOW.setTitle("Obama Game ("+std::to_string(_frameLimiter.getFramerate())+" FPS) (DeltaTime is "+std::to_string(_frameLimiter.deltaTime)+")");

		_frameLimiter.end();
	}
}

void Game::render() {
	glClearDepth(1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	testBatch.begin();

	testBatch.end();

	_rShader.useProgram();
	GLint shaderTime = _rShader.getUniformLocation("time");
	glUniform1f(shaderTime, _time);
	bg.render();
	_rShader.unUseProgram();


	_spriteShader.useProgram();
	txt.render(_spriteShader, _Camera.getCameraMatrix());
	_Player.render(_spriteShader,_Camera,_frameLimiter.deltaTime);
	testBatch.renderBatch();
	_spriteShader.unUseProgram();

	_WINDOW.swapBuffer();
}

void Game::handleInput() {
	SDL_Event action;
	while (SDL_PollEvent(&action) == 1) {
		switch (action.type) {
		case SDL_QUIT:
			_state = GameState::EXIT;
		case SDL_KEYDOWN:
			handleKeyboardDownInput(action); break;
		case SDL_KEYUP:
			handleKeyboardUpInput(action); break;
		}
	}
}

void Game::handleKeyboardDownInput(SDL_Event keyEvent) {
	TypeTest(keyEvent.key, txt);
	if (keyEvent.key.repeat)return;
	switch (keyEvent.key.keysym.sym) {
		case SDLK_ESCAPE:
			_state = GameState::EXIT; break;
		case SDLK_F11:
			_isFullscreen = !_isFullscreen;
			SDL_SetWindowFullscreen(_WINDOW.GetWindowID(), _isFullscreen);
		case SDLK_MINUS:
			_Camera.setScale(_Camera.getScale() - 0.1f); break;
		case SDLK_EQUALS:
			_Camera.setScale(_Camera.getScale() + 0.1f);
	}
	_Player.keyDown(keyEvent.key.keysym.sym);
}

void Game::handleKeyboardUpInput(SDL_Event keyEvent) {
	_Player.keyUp(keyEvent.key.keysym.sym);
}
std::string s;
void Game::TypeTest(SDL_KeyboardEvent key,Text &txtobj) {
	if (key.keysym.sym >= ' ' && key.keysym.sym <= '~')
		s += key.keysym.sym;
	else if (key.keysym.sym == SDLK_BACKSPACE && s.length() > 0)
		s.erase(s.length() - 1); 
	else return;

	txtobj = s;
}