#include "GUI.h"
#include <GL/glew.h>

void Button::render(Camera2D& cam) {
	int ox, oy;

	switch (anchor) {
	case Anchor::RIGHT:
		ox = 1;
		break;
	case Anchor::TOP:
		oy = 1;
		break;
	case Anchor::LEFT:
		ox = -1;
		break;
	case Anchor::BOTTOM:
		oy = -1;
		break;
	case Anchor::TOP_LEFT:
		ox = oy = 1;
		break;
	case Anchor::TOP_RIGHT:
		ox = -1;
		oy = 1;
		break;
	case Anchor::BOTTOM_LEFT:
		ox = oy = -1;
		break;
	case Anchor::BOTTOM_RIGHT:
		ox = 1;
		oy = -1;
		break;
	}


	if (active)  glColor3f(hoverColour.r, hoverColour.g, hoverColour.b);
	else glColor3f(colour.r, colour.g, colour.b);
	
	if (normalised)glRectd(x * 2 + ox, y * 2 + oy, (x + width) * 2 + ox, (y + height) * 2 + oy);
	else glRectd(x * 2 / cam.getWidth() + ox, y * 2 / cam.getHeight() + oy, (x + width) * 2 / cam.getWidth() + ox, (y + height) * 2 / cam.getHeight() + oy);
}

std::vector<Button> GUI::_buttons;
Camera2D* GUI::_camera;

GUI::GUI()
{
}


GUI::~GUI()
{
}

Button* GUI::addButton(Button b) {
	_buttons.push_back(b);
	return &_buttons.back();
}

void GUI::render() {
	for (Button b : _buttons) {
		b.render(*_camera);
	}
}

void GUI::renderText(Font& f,Shader& s) {
	for (Button b : _buttons) {
		int psize = (b.normalised ? b.width * _camera->getWidth() : b.width) / strlen(b.label);
		f.drawString(b.label, 
			b.normalised ? b.x * _camera->getWidth() : b.x, b.normalised ? b.y * _camera->getHeight() : b.y,
			(b.normalised ? b.height * _camera->getHeight() : b.height) < psize ? (b.normalised ? b.height * _camera->getHeight() : b.height) : psize,
			b.textColour.vec4(), s);
	}
}

bool GUI::update(float x,float y) {

	for (Button& b : _buttons) {
		if ((b.normalised ? x / _camera->getWidth() >= b.x && x / _camera->getWidth() <= b.x + b.width :  x >= b.x && x <= b.x + b.width) &&
			(b.normalised ? y / _camera->getHeight()>= b.y && y / _camera->getHeight()<= b.y + b.height : y >= b.y && y <= b.y + b.height)) {

			b.active = true;
			return true;
		}
		else
			b.active = false;
	}
	
	return false;
}

void GUI::click() {
	for (Button &b : _buttons)
		if (b.active)
			b.onClick();
}