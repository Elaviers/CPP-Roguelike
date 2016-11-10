#include "GUI.h"
#include <GL/glew.h>

void UIElement::setAnchor(Anchor::AnchorPoint anchor) {
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

bool Button::update(float mx, float my, Camera2D& cam) {
	if (mx >= (normalised & NORMALISED_X ? (x + (offset_x + 1) / 2) * cam.getWidth() : x + (offset_x + 1) / 2 * cam.getWidth()) &&
		my >= (normalised & NORMALISED_Y ? (y + (offset_y + 1) / 2) * cam.getHeight() : y + (offset_y + 1) / 2 * cam.getHeight()) &&
		mx <= (normalised & NORMALISED_X ? (normalised & NORMALISED_WIDTH ? (x + width + (offset_x + 1) / 2) * cam.getWidth() : (x + (offset_x + 1) / 2) * cam.getWidth() + width) :
			normalised & NORMALISED_WIDTH ? x + (width + (offset_x + 1) / 2) * cam.getWidth() : x + width + offset_x / 2 * cam.getWidth()) &&
		my <= (normalised & NORMALISED_Y ? (normalised & NORMALISED_HEIGHT ? (y + height + (offset_y + 1) / 2) * cam.getHeight() : (y + (offset_y + 1) / 2) * cam.getHeight() + height) :
			normalised & NORMALISED_HEIGHT ? y + (width + (offset_y + 1) / 2) * cam.getHeight() : y + height + (offset_y + 1) / 2 * cam.getHeight()))
		active = true;
	else
		active = false;

	return active;
}

void Button::render(Camera2D& cam) {
	if (active)  glColor3f(hoverColour.r, hoverColour.g, hoverColour.b);
	else glColor3f(colour.r, colour.g, colour.b);
	
	glRectd(x / (normalised & NORMALISED_X ? 1 : cam.getWidth())  * 2 + offset_x,
			y / (normalised & NORMALISED_Y ? 1 : cam.getHeight()) * 2 + offset_y,
			(x / (normalised & NORMALISED_X ? 1 : cam.getWidth()) + width / (normalised & NORMALISED_WIDTH ? 1 : cam.getWidth())) * 2 + offset_x,
			(y / (normalised & NORMALISED_Y ? 1 : cam.getHeight()) + height / (normalised & NORMALISED_HEIGHT ? 1 : cam.getHeight())) * 2 + offset_y);
}

void Button::renderLabel(Font&f,Shader&s,Camera2D&cam) {
	if (label == nullptr)return;
	int psize = (normalised & NORMALISED_WIDTH ? width * cam.getWidth() : width) / strlen(label);
	f.drawString(label,
		normalised & NORMALISED_X ? (x + (offset_x + 1) / 2) * cam.getWidth() : x + (offset_x + 1) / 2 * cam.getWidth(),
		normalised & NORMALISED_Y ? (y + (offset_y + 1) / 2) * cam.getHeight() : y + (offset_y + 1) / 2 * cam.getHeight(),
		(normalised & NORMALISED_HEIGHT ? height * cam.getHeight() : height) < psize ? (normalised & NORMALISED_HEIGHT ? height *cam.getHeight() : height) : psize,
		textColour.vec4(), s);
}

bool TextBox::update(float mx,float my, Camera2D& cam) {
	if (	mx >= (normalised & NORMALISED_X ? (x + (offset_x + 1) / 2) * cam.getWidth() : x + (offset_x + 1) / 2 * cam.getWidth()) &&
			my >= (normalised & NORMALISED_Y ? (y + (offset_y + 1) / 2) * cam.getHeight() : y + (offset_y + 1) / 2 * cam.getHeight()) &&
			mx <= (normalised & NORMALISED_X ? (normalised & NORMALISED_WIDTH ? (x + width + (offset_x + 1) / 2) * cam.getWidth() : (x + (offset_x + 1) / 2) * cam.getWidth() + width) :
			normalised & NORMALISED_WIDTH ? x + (width + (offset_x + 1) / 2) * cam.getWidth() : x + width + offset_x / 2 * cam.getWidth()) &&
			my <= (normalised & NORMALISED_Y ? (normalised & NORMALISED_HEIGHT ? (y + height + (offset_y + 1) / 2) * cam.getHeight() : (y + (offset_y + 1) / 2) * cam.getHeight() + height) :
			normalised & NORMALISED_HEIGHT ? y + (width + (offset_y + 1) / 2) * cam.getHeight() : y + height + (offset_y + 1) / 2 * cam.getHeight()))
		hover = true;
	else
		hover = false;

	return hover;
}

void TextBox::render(Camera2D& cam) {
	if (active) glColor3f(colour2.r, colour2.g, colour2.b);
	else glColor3f(colour.r, colour.g, colour.b);

	glRectd(x / (normalised & NORMALISED_X ? 1 : cam.getWidth()) * 2 + offset_x,
		y / (normalised & NORMALISED_Y ? 1 : cam.getHeight()) * 2 + offset_y,
		(x / (normalised & NORMALISED_X ? 1 : cam.getWidth()) + width / (normalised & NORMALISED_WIDTH ? 1 : cam.getWidth())) * 2 + offset_x,
		(y / (normalised & NORMALISED_Y ? 1 : cam.getHeight()) + height / (normalised & NORMALISED_HEIGHT ? 1 : cam.getHeight())) * 2 + offset_y);
}

void TextBox::renderLabel(Font&f, Shader&s, Camera2D&cam) {
	if (text.c_str() == nullptr)return;
	int psize = (normalised & NORMALISED_WIDTH ? width * cam.getWidth() : width) / text.length();
	f.drawString(text,
		normalised & NORMALISED_X ? (x + (offset_x + 1) / 2) * cam.getWidth() : x + (offset_x + 1) / 2 * cam.getWidth(),
		normalised & NORMALISED_Y ? (y + (offset_y + 1) / 2) * cam.getHeight() : y + (offset_y + 1) / 2 * cam.getHeight(),
		(normalised & NORMALISED_HEIGHT ? height * cam.getHeight() : height) < psize ? (normalised & NORMALISED_HEIGHT ? height *cam.getHeight() : height) : psize,
		textColour.vec4(), s);
}

void TextBox::click() {
	if (active != hover) {
		active = hover;
		onStateChanged(active);
	}
}

void TextBox::textInput(char ch) {
	if (active) {
		text += ch;
	}
}

std::vector<UIElement*> GUI::_elements;
Camera2D* GUI::_camera;

void GUI::add(UIElement& e) {
	_elements.push_back(&e);
}

void GUI::render() {
	for (UIElement* e : _elements) {
		e->render(*_camera);
	}
}

void GUI::renderText(Font& f,Shader& s) {
	for (UIElement* e : _elements) {
		e->renderLabel(f,s,*_camera);
	}
}

bool GUI::update(float x,float y) {
	bool inUse = false;
	for (UIElement* e : _elements) {
		if (e->update(x, y, *_camera))
			inUse = true;
	}

	return inUse;
}

void GUI::click() {
	for (UIElement* e : _elements) {
		e->click();
	}
}