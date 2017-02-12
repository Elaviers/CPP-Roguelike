#include "GUI.h"
#include <GL/glew.h>

Vector2 GUI::cameraScale = Vector2{ 1,1 };

using namespace GUI;

//Global

UIContainer GlobalUI::_root(0,0,1,1,NORMALISED_X | NORMALISED_Y | NORMALISED_WIDTH | NORMALISED_HEIGHT);

bool GlobalUI::overlapping(int x, int y) {
	return _root.isOverlapping(x,y);
}

void GlobalUI::render(Shader &fontShader) {
	_root.render(RenderTypes::NONE,nullptr);

	fontShader.useProgram();
		_root.render(RenderTypes::FONT,&fontShader);
	fontShader.unUseProgram();
}

void GlobalUI::add(UIElement&e) {
	_root.addElement(e,true);
}

void GlobalUI::add(UIElement*e) {
	_root.addElement(e, true);
}

void GlobalUI::setCameraSize(int w,int h) {
	GUI::cameraScale = Vector2{ (float) w,(float) h };
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

////////////////////////////////////////////////////////////////////////////////////TEXTBOX
TextBox::TextBox(float x, float y, float w, float h, unsigned char flags) :
	UIContainer(x, y, w, h, flags)
{
	addElement(panel,false);
	addElement(label,false);
};

void TextBox::click() {
	if (_active != _hover) {
		_active = _hover;
		panel.setColour(_active ? _selectColour : _colour);
		onStateChanged(_active);
	}
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