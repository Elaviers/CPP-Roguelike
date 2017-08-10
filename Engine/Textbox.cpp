#include "Textbox.h"

using namespace GUI;

TextBox::TextBox(float x, float y, float w, float h, unsigned char flags) :
	UIContainer(x, y, w, h, flags)
{
	addElement(panel, false);
	addElement(label, false);
};

bool TextBox::click() {
	if (_active != _hover) {
		_active = _hover;
		panel.setColour(_active ? _selectColour : _colour);
		if (onStateChanged) onStateChanged(_active);
		return true;
	}
	return false;
}

bool TextBox::isOverlapping(int x, int y) {
	_hover = panel.isOverlapping(x, y);

	return _hover;
}

void TextBox::textInput(char ch) {
	if (_active) {
		label.push(ch);
	}
}
