#pragma once
#include "Font.h"
#include "NormalisedColour.h"
#include "UIElement.h"

namespace GUI {
	class UIText : public UIElement
	{
	private:
		NormalisedColour _colour;
		Font* _font;
	public:
		std::string text;
		void setColour(const NormalisedColour &colour) { _colour = colour; };
		void setFont(const std::string& font);

		void render(Shader*) override;

		const std::string& operator=(const std::string& rhs) { text = rhs; return text; };

		UIText(float x, float y, float w, float h, unsigned char f) : UIElement(x, y, w, h, f) {};
		UIText() {};
		~UIText() { std::printf("Destroy UITEXT (%p)\n", this); };
	};
}
