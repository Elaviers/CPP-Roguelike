#include "GUI.h"
#include <GL/glew.h>

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

void GUI::render(Camera2D& cam) {
	int ox, oy;

	for (Button b : _buttons) {
		switch (b.anchor) {
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


		if (b.active)  glColor3f(b.hoverColour.r,b.hoverColour.g,b.hoverColour.b);
		else glColor3f(b.colour.r, b.colour.g, b.colour.b);
		glRectd(b.x * 2 + ox, b.y * 2 + oy, b.x * 2 + b.width * 2 + ox, b.y * 2 + b.height * 2 + oy);
	}
}

void GUI::renderText(Font& f,Shader& s) {
	for (Button b : _buttons) {
		f.drawString(b.label, b.x * _camera->getWidth(), b.y * _camera->getHeight(),
			(b.height * _camera->getHeight()) < f.getPointSize() ? b.height * _camera->getHeight() : (b.width * _camera->getWidth()) / strlen(b.label),
			b.textColour.vec4(), s);
	}
}

bool GUI::getActiveButton(float x,float y,Button& ret) {
	x /= _camera->getWidth();
	y /= _camera->getHeight();

	for (Button &b : _buttons)
		if (x >= b.x && x <= b.x + b.width && y >= b.y && y <= b.y + b.height) {
			b.active = true;
			ret = b;
			return true;
		}
		else
			b.active = false;
	
	return false;
}