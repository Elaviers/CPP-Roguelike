#include "Window.h"

#include "ErrorHandling.h"

Window::Window() {
}


Window::~Window() {
}

int Window::create(std::string title, int width, int height, unsigned int flag) {
	_w = width; _h = height;

	unsigned int windowFlag = SDL_WINDOW_OPENGL | flag;

	/*if (flag & HIDDEN)
		windowFlag |= SDL_WINDOW_HIDDEN;
	if (flag & FULLSCREEN)
		windowFlag |= SDL_WINDOW_FULLSCREEN;
	if (flag & BORDERLESS)
		windowFlag |= SDL_WINDOW_BORDERLESS;*/

	_ID = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _w, _h, windowFlag);
	if (_ID == nullptr)
		error("I could not create the window, you fool!");

	SDL_GLContext context = SDL_GL_CreateContext(_ID);
	if (context == nullptr)
		error("I couldn't create the window context. How can this even happen?");

	if (glewInit() != GLEW_OK)
		error("Glew has issues, bro!");

	return 0;
}

void Window::swapBuffer() {
	SDL_GL_SwapWindow(_ID);
}

void Window::setTitle(std::string t) {
	SDL_SetWindowTitle(_ID,t.c_str());
}
