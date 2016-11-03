#include "GUI.h"
#include <GL/glew.h>

void Button::setAnchor(Anchor::AnchorPoint anchor) {
	switch (anchor) {
	case Anchor::RIGHT:
		offset_x = 1;
		break;
	case Anchor::TOP:
		offset_y = 1;
		break;
	case Anchor::LEFT:
		offset_x = -1;
		break;
	case Anchor::BOTTOM:
		offset_y = -1;
		break;
	case Anchor::TOP_LEFT:
		offset_x = -1;
		offset_y = 1;
		break;
	case Anchor::TOP_RIGHT:
		offset_x = offset_y = 1;
		break;
	case Anchor::BOTTOM_LEFT:
		offset_x = offset_y = -1;
		break;
	case Anchor::BOTTOM_RIGHT:
		offset_x = 1;
		offset_y = -1;
		break;
	}
}

void Button::render(Camera2D& cam) {
	if (active)  glColor3f(hoverColour.r, hoverColour.g, hoverColour.b);
	else glColor3f(colour.r, colour.g, colour.b);
	
	glRectd(x / (normalised & NORMALISED_X ? 1 : cam.getWidth())  * 2 + offset_x,
			y / (normalised & NORMALISED_Y ? 1 : cam.getHeight()) * 2 + offset_y,
			(x / (normalised & NORMALISED_X ? 1 : cam.getWidth()) + width / (normalised & NORMALISED_WIDTH ? 1 : cam.getWidth())) * 2 + offset_x,
			(y / (normalised & NORMALISED_Y ? 1 : cam.getHeight()) + height / (normalised & NORMALISED_HEIGHT ? 1 : cam.getHeight())) * 2 + offset_y);
}

std::vector<Button> GUI::_buttons;
Camera2D* GUI::_camera;

GUI::GUI()
{
}


GUI::~GUI()
{
}

Button* GUI::addButton(Button& b) {
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
		if (b.label == nullptr)continue;
		int psize = (b.normalised & NORMALISED_WIDTH ? b.width * _camera->getWidth() : b.width) / strlen(b.label);
		f.drawString(b.label,
			b.normalised & NORMALISED_X ? (b.x + (b.offset_x + 1) / 2) * _camera->getWidth()  : b.x + (b.offset_x + 1) / 2 * _camera->getWidth(),
			b.normalised & NORMALISED_Y ? (b.y + (b.offset_y + 1) / 2) * _camera->getHeight() : b.y + (b.offset_y + 1) / 2 * _camera->getHeight(),
			(b.normalised & NORMALISED_HEIGHT ? b.height * _camera->getHeight() : b.height) < psize ? (b.normalised & NORMALISED_HEIGHT ? b.height * _camera->getHeight() : b.height) : psize,
			b.textColour.vec4(), s);
	}
}

bool GUI::update(float x,float y) {
	bool inUse = false;

	for (Button& b : _buttons) {
		/*if (b.debug)printf("BUTTON (%s)...\nX\n%f > %f\n%f < %f\nY\n%f > %f\n%f < %f\n\n", b.label, x, (b.normalised & NORMALISED_X ? (b.x + (b.offset_x + 1) / 2) * _camera->getWidth() : b.x + (b.offset_x + 1) / 2 * _camera->getWidth()),
			x, (b.normalised & NORMALISED_X ? (b.normalised & NORMALISED_WIDTH ? (b.x + b.width + (b.offset_x + 1) / 2) * _camera->getWidth() : (b.x + (b.offset_x + 1) / 2) * _camera->getWidth() + b.width) :
				b.normalised & NORMALISED_WIDTH ? b.x + (b.width + (b.offset_x + 1) / 2) * _camera->getWidth() : b.x + b.width + b.offset_x / 2 * _camera->getWidth()),
			y, (b.normalised & NORMALISED_Y ? (b.y + (b.offset_y + 1) / 2) * _camera->getHeight() : b.y + (b.offset_y + 1) / 2 * _camera->getHeight()),
			y, (b.normalised & NORMALISED_Y ? (b.normalised & NORMALISED_HEIGHT ? (b.y + b.height + (b.offset_y + 1) / 2) * _camera->getHeight() : (b.y + (b.offset_y + 1) / 2) * _camera->getHeight() + b.height) :
				b.normalised & NORMALISED_HEIGHT ? b.y + (b.width + (b.offset_y + 1) / 2) * _camera->getHeight() : b.y + b.height + (b.offset_y + 1) / 2 * _camera->getHeight())); //Debug stuff*/

		if (x >= (b.normalised & NORMALISED_X ? (b.x + (b.offset_x + 1) / 2) * _camera->getWidth() :  b.x + (b.offset_x + 1) / 2 * _camera->getWidth()) &&
			y >= (b.normalised & NORMALISED_Y ? (b.y + (b.offset_y + 1) / 2) * _camera->getHeight() : b.y + (b.offset_y + 1) / 2 * _camera->getHeight()) &&
			x <= (b.normalised & NORMALISED_X ? (b.normalised & NORMALISED_WIDTH ? (b.x + b.width + (b.offset_x + 1) / 2) * _camera->getWidth() : (b.x + (b.offset_x + 1) / 2) * _camera->getWidth() + b.width) :
					b.normalised & NORMALISED_WIDTH ? b.x + (b.width + (b.offset_x + 1) / 2) * _camera->getWidth() : b.x + b.width + b.offset_x / 2 * _camera->getWidth()) &&
			y <= (b.normalised & NORMALISED_Y ? (b.normalised & NORMALISED_HEIGHT ? (b.y + b.height + (b.offset_y + 1) / 2) * _camera->getHeight() : (b.y + (b.offset_y + 1) / 2) * _camera->getHeight() + b.height) :
					b.normalised & NORMALISED_HEIGHT ? b.y + (b.width + (b.offset_y + 1) / 2) * _camera->getHeight() : b.y + b.height + (b.offset_y + 1) / 2 * _camera->getHeight()))
			///////////////////////////
			b.active = inUse = true;
		else
			b.active = false;
	}
	
	return inUse;
}

void GUI::click() {
	for (Button &b : _buttons)
		if (b.active)
			b.onClick();
}