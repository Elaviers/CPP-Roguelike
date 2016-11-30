#include "UIPrimitives.h"

using namespace GUI;

////////////////|UIELEMENT|
UIElement::UIElement(float x, float y, float w, float h, unsigned char flags) : _flags(flags) {
	setX(x);
	setY(y);
	setWidth(w);
	setHeight(h);
}
////////
Vector2 UIElement::_cameraSize;
////////
void UIElement::setX(float x) {
	if (!_flags & NORMALISED_X)x /= _cameraSize.x;//Normalise if needed
	if (_flags & ONEMINUS_X)x = 1 - x;
	if (_parent)x = _parent->getX() + x * _parent->getWidth();

	_corner1.x = x;
}

void UIElement::setY(float y) {
	if (!(_flags & NORMALISED_Y))y /= _cameraSize.y;//Normalise if needed
	if ((_flags & ONEMINUS_Y))y = 1 - y;
	if (_parent)y = _parent->getY() + y * _parent->getHeight();

	_corner1.y = y;
}

void UIElement::setWidth(float width) {
	if (!(_flags & NORMALISED_WIDTH))width /= _cameraSize.x;//Normalise if needed
	if (_parent)width = width * _parent->getWidth();

	_corner2.x = _corner1.x + width;
}

void UIElement::setHeight(float height) {
	if (!(_flags & NORMALISED_HEIGHT))height /= _cameraSize.y;//Normalise if needed
	if (_parent)height = height * _parent->getHeight();

	_corner2.y = _corner1.y + height;
}

bool UIElement::isOverlapping(int x, int y) {
	float fx = x / _cameraSize.x;
	float fy = y / _cameraSize.y;

	if (fx > _corner1.x && fx < _corner2.x && fy > _corner1.y && fy < _corner2.y)
		return true;
	return false;
}

void UIElement::recalculate(int newW, int newH) {
	//if (!flags & NORMALISED_X)
}
////////////////|UIROOT|
void UIRoot::render(Font &a,Shader &b) 
{
	for (UIElement*& e : _elements)
		e->render(a, b);
}

void UIRoot::click() {
	for (UIElement*& e : _elements)
		e->click();
}

bool UIRoot::isOverlapping(int x, int y) {
	for (UIElement*& e : _elements)
		if (e->isOverlapping(x,y)) 
			return true;
	return false;
}
////////////////|UIRECT|
void UIRect::render(Font&,Shader&) 
{
	//glColor4f(_colour.r,_colour.g,_colour.b,_colour.a);
	glRectf(_corner1.x * 2 - 1,_corner1.y * 2 - 1,_corner2.x * 2 - 1,_corner2.y * 2 - 1);
}
////////////////|UITEXT|
void UIText::render(Font& font, Shader& fontShader) {
	//font.drawString(label,_corner1.x)
}