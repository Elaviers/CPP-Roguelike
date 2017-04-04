#pragma once
#include <Engine/Button.h>

namespace UI_Constants {
	extern const NormalisedColour rect_Primary, rect_Secondary, text_Primary;
}

class UI_Button : public GUI::Button {
public:
	UI_Button();
	~UI_Button();

};
