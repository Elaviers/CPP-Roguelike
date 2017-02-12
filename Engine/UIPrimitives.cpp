#include "UIPrimitives.h"

#include "LineRenderer.h"

using namespace GUI;

////////////////|UIELEMENT|
UIElement::UIElement(float x, float y, float w, float h, unsigned char flags) : _flags(flags), _position{ x, y }, _size{ w, h } {}
////////

bool UIElement::isOverlapping(int x, int y) {
	float fx = x / cameraScale.x;
	float fy = y / cameraScale.y;

	if (fx >= _corner1.x && fx <= _corner2.x && fy >= _corner1.y && fy <= _corner2.y)
		return true;
	return false;
}

void UIElement::calculate() {
	float x = _position.x, y = _position.y;
	float width = _size.x, height = _size.y;
	
	if (!_flags & NORMALISED_X)x /= cameraScale.x;//Normalise if needed
	if (_flags & ONEMINUS_X)x = 1 - x;

	if (!(_flags & NORMALISED_Y))y /= cameraScale.y;//Normalise if needed
	if ((_flags & ONEMINUS_Y))y = 1 - y;

	if (!(_flags & NORMALISED_WIDTH))width /= cameraScale.x;//Normalise if needed
	if (!(_flags & NORMALISED_HEIGHT))height /= cameraScale.y;//Normalise if needed

	if (_parent)x = _parent->getX() + x * _parent->getWidth();
	if (_parent)y = _parent->getY() + y * _parent->getHeight();
	if (_parent)width = width * (_parent->getWidth());
	if (_parent)height = height * (_parent->getHeight());

	std::printf("CALCULATE %p : PARENT IS %p : CAMERASCALE IS %d %d (%f %f %f %f -> %f %f %f %f)\n",
		this,_parent,
		(int)cameraScale.x,(int)cameraScale.y,
		_position.x, _position.y, _position.x + _size.x, _position.x + _size.y,
		x,y,x+width,y+height);

	_corner1.x = x;
	_corner1.y = y;
	_corner2.x = x + width;
	_corner2.y = y + height;
}
////////////////|UIROOT|
void UIContainer::render(RenderTypes::RenderType type,Shader *s) 
{
	for (UIElement*& e : _elements)
		e->render(type,s);
}

void UIContainer::click() {
	for (UIElement*& e : _elements)
		e->click();
}

bool UIContainer::isOverlapping(int x, int y) {
	bool val = false;
	for (UIElement*& e : _elements)
		if (e->isOverlapping(x,y)) 
			val = true;
	return val;
}

void UIContainer::calculate() {
	UIElement::calculate();

	for (UIElement*& e : _elements)
		e->calculate();
}
////////////////|UIRECT|
void UIRect::render(RenderTypes::RenderType type, Shader *s) {	
	if (type == RenderTypes::NONE) {
		glColor4f(_colour.r, _colour.g, _colour.b, _colour.a);
		glRectf(_corner1.x * 2 - 1, _corner1.y * 2 - 1, _corner2.x * 2 - 1, _corner2.y * 2 - 1);
	}
}
////////////////|UITEXT|
void UIText::render(RenderTypes::RenderType type, Shader *fontShader) {
	if (!_font.loaded) {
		std::printf("Warning:attempted to render UIText without a loaded font!\n");
		return;
	}

	if (type == RenderTypes::FONT)
		_font.drawString(text, _corner1.x * cameraScale.x, _corner1.y * cameraScale.y,
			(text.length() * cameraScale.y * getHeight() > cameraScale.x * getWidth()) ? (int)((cameraScale.x * getWidth()) / text.length()) : (int)(cameraScale.y * getHeight()),
			_colour.vec4(), *fontShader);
}