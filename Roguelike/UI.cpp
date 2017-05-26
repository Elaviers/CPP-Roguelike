#include "UI.h"

const NormalisedColour UI_Constants::rect_Primary(0, 0.5f, 0), UI_Constants::rect_Secondary(1, 1, 1), UI_Constants::text_Primary(0, 0, 0);

using namespace GUI;

UI_Button::UI_Button() : Button(0, 0, 1, 32, NORMALISED_WIDTH) {
	this->label = "butts";
	this->setColour(UI_Constants::rect_Secondary);
	this->setHoverColour(UI_Constants::rect_Primary);
	this->label.setColour(UI_Constants::text_Primary);
}

UI_Button::~UI_Button() {

}
