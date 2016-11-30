#include "GUI.h"
#include <GL/glew.h>

using namespace GUI;

////////////////////////////////////////////////////////////////////////////////////BUTTON
void Button::render(Font& f, Shader& s) {
	panel.render(f,s);
	label.render(f,s);
}

bool Button::isOverlapping(int x,int y) {
	_active = panel.isOverlapping(x, y);
	return _active;
}

////////////////////////////////////////////////////////////////////////////////////TEXTBOX

void TextBox::render(Font&f, Shader& s) {
	panel.render(f,s);
	label.render(f,s);
}

void TextBox::click() {
	if (_active != _hover) {
		_active = _hover;
		onStateChanged(_active);
	}
}

void TextBox::textInput(char ch) {
	if (_active) {
		label.text += ch;
	}
}

////////////////////////////////////////////////////////////////////////////////////GUI
std::vector<UIElement*> Handler::_elements;
Camera2D* Handler::_camera;

void Handler::add(UIElement& e) {
	_elements.push_back(&e);
}

void Handler::render(Font& f,Shader& s) {
	for (UIElement* e : _elements) {
		e->render(f,s);
	}
}

bool Handler::update(int x,int y) {
	bool inUse = false;
	for (UIElement* e : _elements) {
		if (e->isOverlapping(x, y))
			inUse = true;
	}

	return inUse;
}

void Handler::click() {
	for (UIElement* e : _elements) {
		e->click();
	}
}