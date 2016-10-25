#include "Controller.h"

bool u, d, l, r;
Sprite test;

void Controller::init() {
	test.UVGridDivisions = 8;
	test.init(0, 0, 64, 64, false, "tiles.png");
}

int gridSnap(int i,int snap) {
	if (i % snap > 0)
		return i - (i % snap);
	else return i - snap - (i % snap);
}

void Controller::render(float deltaTime,Camera2D& cam) {
	cam.move(_moveX * speed * deltaTime, _moveY * speed * deltaTime);
	test.setPosition(gridSnap(cam.getPosition().x + _mouseX,64),gridSnap(cam.getPosition().y + _mouseY,64));
	test.render();
}

void Controller::input(SDL_Event event, int screenh)
{
	SDL_GetMouseState(&_mouseX,&_mouseY);
	_mouseY = screenh - _mouseY;

	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym) {
		case SDLK_w:u = true; break;
		case SDLK_s:d = true; break;
		case SDLK_a:l = true; break;
		case SDLK_d:r = true; break;
		}

		_moveX = l ? (r ? 0 : -1) : r ? 1 : 0;
		_moveY = u ? (d ? 0 : 1) : d ? -1 : 0;

	}
	else if (event.type == SDL_KEYUP) {
		switch (event.key.keysym.sym) {
		case SDLK_w:u = false; break;
		case SDLK_s:d = false; break;
		case SDLK_a:l = false; break;
		case SDLK_d:r = false; break;
		}

		_moveX = l ? (r ? 0 : -1) : r ? 1 : 0;
		_moveY = u ? (d ? 0 : 1) : d ? -1 : 0;
	}
	else if (event.type == SDL_MOUSEWHEEL) {
		if (event.wheel.y > 0)
			_CameraScale += 0.1f;
		else if (event.wheel.y < 0)
			_CameraScale -= 0.1f;
	}
}