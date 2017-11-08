#pragma once
#include <Engine/UIButton.h>

namespace UI_Constants {
	extern const NormalisedColour rect_Primary, rect_Secondary, text_Primary;
}

class UI_Button : public UIButton {
public:
	UI_Button();
	~UI_Button();

};
