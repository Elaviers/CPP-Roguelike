#include "GUI.h"
#include <GL/glew.h>
#include "RenderType.h"

Vector2f GUI::cameraScale = Vector2f{ 1,1 };

using namespace GUI;

//Global

UIContainer GlobalUI::_root(0,0,1,1,NORMALISED_X | NORMALISED_Y | NORMALISED_WIDTH | NORMALISED_HEIGHT);

bool GlobalUI::updateMousePosition(int x, int y) {
	return _root.isOverlapping(x,y);
}

void GlobalUI::render(Shader *shader) {
	if (!shader) {
		_root.render(nullptr);
		return;
	}

	if (shader->Channel == RenderTypes::FONT)
		_root.render(shader);
}

void GlobalUI::add(UIElement&e) {
	_root.addElement(e,true);
}

void GlobalUI::add(UIElement*e) {
	_root.addElement(e, true);
}

void GlobalUI::remove(UIElement* e) {
	_root.removeElement(e);
}

void GlobalUI::setCameraSize(int w,int h) {
	GUI::cameraScale = Vector2f{ (float) w,(float) h };
	_root.calculate();
}

void GlobalUI::click() {
	_root.click();
}

////////////////////////////////////////////////////////////////////////////////////BUTTON
Button::Button(float x, float y, float w, float h, unsigned char flags) :
	UIContainer(x, y, w, h, flags)
{
	addElement(panel, false);
	addElement(label, false);
};

bool Button::isOverlapping(int x,int y) {
	_active = panel.isOverlapping(x, y);

	panel.setColour(_active ? _hoverColour : _colour);

	return _active;
}

bool Button::click() { 
	if (_active) {
		if (onClick != nullptr)
			onClick();
		return true;
	}
	return false;
}

////////////////////////////////////////////////////////////////////////////////////TEXTBOX
TextBox::TextBox(float x, float y, float w, float h, unsigned char flags) :
	UIContainer(x, y, w, h, flags)
{
	addElement(panel,false);
	addElement(label,false);
};

bool TextBox::click() {
	if (_active != _hover) {
		_active = _hover;
		panel.setColour(_active ? _selectColour : _colour);
		onStateChanged(_active);
		return true;
	}
	return false;
}

bool TextBox::isOverlapping(int x,int y) {
	_hover = panel.isOverlapping(x, y);

	return _hover;
}

void TextBox::textInput(char ch) {
	if (_active) {
		label.text += ch;
	}
}