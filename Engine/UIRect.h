#pragma once
#include "NormalisedColour.h"
#include "UIElement.h"

	class UIRect : public UIElement
	{
	private:
		NormalisedColour _colour;
	public:
		void setColour(const NormalisedColour &colour) { _colour = colour; };

		void render(Shader*) override;

		UIRect(float x, float y, float w, float h, unsigned char f) : UIElement(x, y, w, h, f) {};
		UIRect() {};
		~UIRect() {};
};
