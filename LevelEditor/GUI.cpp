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
	
	glRectd(x / (normalised & NORMALISED_X ? 1 : cam.getWidth())  * 2 + ox,
			y / (normalised & NORMALISED_Y ? 1 : cam.getHeight()) * 2 + oy,
			(x / (normalised & NORMALISED_X ? 1 : cam.getWidth()) + width / (normalised & NORMALISED_WIDTH ? 1 : cam.getWidth())) * 2 + ox,
			(y / (normalised & NORMALISED_Y ? 1 : cam.getHeight()) + height / (normalised & NORMALISED_HEIGHT ? 1 : cam.getHeight())) * 2 + oy);
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
		int psize = (b.normalised & NORMALISED_WIDTH ? b.width * _camera->getWidth() : b.width) / strlen(b.label);
		f.drawString(b.label, 
			b.normalised & NORMALISED_X ? b.x * _camera->getWidth() : b.x, b.normalised * NORMALISED_Y ? b.y * _camera->getHeight() : b.y,
			(b.normalised & NORMALISED_HEIGHT ? b.height * _camera->getHeight() : b.height) < psize ? (b.normalised & NORMALISED_HEIGHT ? b.height * _camera->getHeight() : b.height) : psize,
			b.textColour.vec4(), s);
	}
}

bool GUI::update(float x,float y) {

	for (Button& b : _buttons) {
		if (x >= (b.normalised & NORMALISED_X ? b.x * _camera->getWidth() : b.x) &&
			y >= (b.normalised & NORMALISED_Y ? b.y * _camera->getHeight() : b.y) &&
			x <= (b.normalised & NORMALISED_WIDTH ? (b.x + b.width) * _camera->getWidth() : b.x + b.width) &&
			y <= (b.normalised & NORMALISED_HEIGHT ? (b.y + b.height) * _camera->getHeight() : b.y + b.height))
		{
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