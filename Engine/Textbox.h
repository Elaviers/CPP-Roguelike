#pragma once
#include "UIContainer.h"
#include "UIRect.h"
#include "UIText.h"

namespace GUI {
	class TextBox : public UIContainer {
	private:
		bool _hover, _active;
		NormalisedColour _colour, _selectColour;
	public:
		TextBox(float x, float y, float width, float height, unsigned char flags);
		virtual ~TextBox() { std::printf("Destroy TextBox (%p)\n", this); };

		void setColour(const NormalisedColour& c) { _colour = c; panel.setColour(c); };
		void setSelectColour(const NormalisedColour& c) { _selectColour = c; };

		UIRect panel;
		UIText label;

		void(*onStateChanged)(bool state);

		bool isOverlapping(const int, const int) override;
		bool click() override;

		void textInput(char newchar);
	};
}
