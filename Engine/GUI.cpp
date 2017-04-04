#include "GUI.h"
#include "RenderType.h"
#include "Vector2f.h"

#include <GL/glew.h>

using namespace GUI;

Vector2f GUI::cameraScale = Vector2f{ 1,1 };

//Global

UIContainer GlobalUI::_root(0,0,1,1,NORMALISED_X | NORMALISED_Y | NORMALISED_WIDTH | NORMALISED_HEIGHT);
std::vector<UIElement*> GlobalUI::_elementsToDelete;

void GlobalUI::clear() {
	std::vector<UIElement*> *elements = _root.getChildren();
	while (elements->size() > 0)
		delete elements->back();
}

bool GlobalUI::update(int x, int y) {
	while (_elementsToDelete.size() > 0) {
		_root.removeElement(_elementsToDelete.back());
		_elementsToDelete.pop_back();
	}
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

void GlobalUI::deleteElement(UIElement* e) {
	_elementsToDelete.push_back(e);
}

void GlobalUI::setCameraSize(int w,int h) {
	GUI::cameraScale = Vector2f{ (float) w,(float) h };
	_root.calculate();
}

void GlobalUI::click() {
	_root.click();
}

////////////////////////////////////////////////////////////////////////////////////BUTTON


////////////////////////////////////////////////////////////////////////////////////TEXTBOX
