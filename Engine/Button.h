#pragma once
#include "UIContainer.h"
#include "UIRect.h"
#include "UIText.h"

namespace GUI {
	class Button : public UIContainer {
	private:
		bool _active;
		NormalisedColour _colour, _hoverColour;

		void(*_event_onClick)(UIElement *caller);
		void(*_event_onClick_basic)();
	public:
		Button(float x, float y, float width, float height, unsigned char flags);
		virtual ~Button() { std::printf("Destroy Button (%p)\n", this); };

		void setColour(const NormalisedColour& c) { _colour = c; panel.setColour(c); };
		void setHoverColour(const NormalisedColour& c) { _hoverColour = c; };

		UIRect panel;
		UIText label;

		bool isOverlapping(const int, const int) override;
		bool click() override;

		void bind_onClick(void(*function)(UIElement *caller)) { _event_onClick = function; };
		void bind_onClick(void(*function)()) { _event_onClick_basic = function; };
	};
}
