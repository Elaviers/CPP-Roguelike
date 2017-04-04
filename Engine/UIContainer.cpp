#include "UIContainer.h"

#include <algorithm>

using namespace GUI;

UIContainer::~UIContainer() {
	std::printf("Start destroying UIContainer.. (%p)\n", this);

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
		if ((*e)->isOverlapping(x, y))
			val = true;
	return val;
}

void UIContainer::calculate() {
	UIElement::calculate();

	for (auto e = _elements.begin(); e != _elements.end(); e++)
		(*e)->calculate();
}