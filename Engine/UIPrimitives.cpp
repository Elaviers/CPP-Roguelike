#include "UIPrimitives.h"

#include "LineRenderer.h"
#include "RenderType.h"
#include "ResourceManager.h"

#include <algorithm>

using namespace GUI;

////////////////|UIELEMENT|
UIElement::UIElement(float x, float y, float w, float h, unsigned char flags) : _flags(flags), _position{ x, y }, _size{ w, h } {}
////////

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
		this,_parent,
		(int)cameraScale.x,(int)cameraScale.y,
		_position.x, _position.y, _size.x, _size.y,
		x,y,x+width,y+height);

	_min.x = width < 0 ? x + width : x;
	_min.y = height < 0 ? y + height : y;
	_max.x = width > 0 ? x + width : x;
	_max.y = height > 0 ? y + height : y;
}

UIContainer::~UIContainer() {
	std::printf("Start destroying UIContainer.. (%p)\n",this);

	while (_elements.size() > 0) {
		std::printf("delete %p...\n", _elements.back());
		delete _elements.back();
	}

	std::printf("done!\n");
}

void UIContainer::removeElement(UIElement* e) {
	_elements.erase(std::remove(_elements.begin(), _elements.end(), e), _elements.end());
}

void UIContainer::render(Shader *s) {
	for (auto e = _elements.begin(); e != _elements.end(); e++)
		(*e)->render(s);
}

bool UIContainer::click() {
	for (auto e = _elements.begin(); e != _elements.end(); e++) {
		if ((*e)->click())
			return true;
	}
	return false;
}

bool UIContainer::isOverlapping(const int x, const int y) {
	bool val = false;
	for (auto e = _elements.begin(); e != _elements.end(); e++)
		if ((*e)->isOverlapping(x,y)) 
			val = true;
	return val;
}

void UIContainer::calculate() {
	UIElement::calculate();

	for (auto e = _elements.begin(); e != _elements.end(); e++)
		(*e)->calculate();
}
////////////////|UIRECT|
void UIRect::render(Shader *s) {	
	if (!s || s->Channel == RenderTypes::NONE) {
		glColor4f(_colour.r, _colour.g, _colour.b, _colour.a);
		glRectf(_min.x * 2 - 1, _min.y * 2 - 1, _max.x * 2 - 1, _max.y * 2 - 1);
	}
}
////////////////|UITEXT|
void UIText::setFont(const std::string& path) {
	_font = ResourceManager::getFontRef(path);
}

void UIText::render(Shader *shader) {
	if (!_font->loaded) {
		std::printf("Warning:attempted to render UIText without a loaded font!\n");
		return;
	}

	if (shader && shader->Channel == RenderTypes::FONT)
		_font->drawString(text, _min.x * cameraScale.x, _min.y * cameraScale.y,
			(text.length() * cameraScale.y * getHeight() > cameraScale.x * getWidth()) ? (int)((cameraScale.x * getWidth()) / text.length()) : (int)(cameraScale.y * getHeight()),
			_colour.vec4(), *shader);
}
