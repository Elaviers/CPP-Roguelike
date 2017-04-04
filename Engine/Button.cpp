#include "Button.h"

using namespace GUI;

Button::Button(float x, float y, float w, float h, unsigned char flags) :
	UIContainer(x, y, w, h, flags)
{
	addElement(panel, false);
	addElement(label, false);
};

bool Button::isOverlapping(int x, int y) {
	_active = panel.isOverlapping(x, y);

	panel.setColour(_active ? _hoverColour : _colour);

	return _active;
}

bool Button::click() {
	if (_active) {
		if (_event_onClick_basic != nullptr)
			_event_onClick_basic();
		if (_event_onClick != nullptr)
			_event_onClick(this);
		return true;
	}
	return false;
}