#include "UIElement.h"

#include "UIContainer.h"

using namespace GUI;

UIElement::UIElement(float x, float y, float w, float h, unsigned char flags) : _flags(flags), _position{ x, y }, _size{ w, h } {

}

UIElement::~UIElement() {
	if (_parent) {
		UIContainer * owner = dynamic_cast<UIContainer*>(_parent);
		if (owner)
			owner->removeElement(this);
	}
}

bool UIElement::isOverlapping(const int x, const int y) {
	float fx = x / cameraScale.x;
	float fy = y / cameraScale.y;

	if (fx >= _min.x && fx <= _max.x && fy >= _min.y && fy <= _max.y)
		return true;
	return false;
}

void UIElement::calculate() {
	float x = _position.x, y = _position.y;
	float width = _size.x, height = _size.y;

	if (!(_flags & NORMALISED_X))x /= cameraScale.x;//Normalise if needed
	if (_flags & FLIPPED_X)x = 1 - x;

	if (!(_flags & NORMALISED_Y))y /= cameraScale.y;//Normalise if needed
	if (_flags & FLIPPED_Y)y = 1 - y;

	if (!(_flags & NORMALISED_WIDTH))width /= cameraScale.x;//Normalise if needed
	if (!(_flags & NORMALISED_HEIGHT))height /= cameraScale.y;//Normalise if needed

	if (_parent)x = _parent->getX() + x * _parent->getWidth();
	if (_parent)y = _parent->getY() + y * _parent->getHeight();
	if (_parent)width = width * (_parent->getWidth());
	if (_parent)height = height * (_parent->getHeight());

	std::printf("CALCULATE %p : PARENT IS %p : CAMERASCALE IS %d %d (%f %f %f %f -> %f %f %f %f)\n",
		this, _parent,
		(int)cameraScale.x, (int)cameraScale.y,
		_position.x, _position.y, _size.x, _size.y,
		x, y, x + width, y + height);

	_min.x = width < 0 ? x + width : x;
	_min.y = height < 0 ? y + height : y;
	_max.x = width > 0 ? x + width : x;
	_max.y = height > 0 ? y + height : y;
}
