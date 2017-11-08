#include "Window.h"

#include "ErrorHandling.h"

#include <GL/glew.h>

Window::Window() {
}


Window::~Window() {
}

int Window::create(const char* title, int width, int height, unsigned int flag) {
	_w = width; _h = height;

	unsigned int windowFlag = SDL_WINDOW_OPENGL | flag;

	_ID = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _w, _h, windowFlag);
	if (_ID == nullptr)
		error("I could not create the window, you fool!");

	_context = SDL_GL_CreateContext(_ID);
	if (_context == nullptr)
		error("I couldn't create the window context. How can this even happen?");

	if (glewInit() != GLEW_OK)
		error("Glew has issues, bro!");

	return 0;
}

void Window::swapBuffer() {
	SDL_GL_SwapWindow(_ID);
}

void Window::setTitle(const char* t) {
	SDL_SetWindowTitle(_ID, t);
}

void Window::useContext() {
	SDL_GL_MakeCurrent(_ID, _context);
}
