#include "Editor.h"

void Editor::start() {
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_GL_SetSwapInterval(0);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	_window.create("Level Editor", screenX, screenY,SDL_WINDOW_RESIZABLE);

	glClearColor(.125, .125, .125, 1);
	////////////////////////////////////////////////////////////////////////

	_camera.SetViewportSize(screenX, screenY);
	_camera.setPosition(-screenX / 2, -screenY / 2);
	_controller.init();

	_shader.loadPreset(ShaderPreset::SPRITE);
	_shader.link();

	LineRenderer::init();
	
	Colour c;

	for (int x = -16; x <= 16; x++) {
		c = (x == 0) ? Colour(32,128,255) : Colour(0,0,0);
		LineRenderer::drawLine(x * 64, -16 * 64, x * 64, 16 * 64, c);
		LineRenderer::drawLine(-16 * 64, x * 64, 16 * 64, x * 64, c);
	}

	running = true;
	while (running) {
		_frameCounter.begin();
		windowInput();
		_camera.update();
		render(_frameCounter.deltaTime);
		_frameCounter.end();
	}

}

void Editor::render(float deltaTime) {
	glClear(GL_COLOR_BUFFER_BIT);

	LineRenderer::render(_camera);

	_shader.useProgram();
	_shader.setMat4("projection",_camera.getCameraMatrix());
	_controller.render(deltaTime,_camera);
	_shader.unUseProgram();

	_window.swapBuffer();

}

void Editor::windowInput() {
	SDL_Event event;
	if (SDL_PollEvent(&event) == 1) {
		_controller.input(event,screenY);
		if (event.type == SDL_QUIT)
			running = false;
		if (event.type == SDL_WINDOWEVENT)
			if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
				screenX = event.window.data1;
				screenY = event.window.data2;
				glViewport(0,0,screenX,screenY);
				_camera.SetViewportSize(screenX,screenY);
			}
	}
}