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
		std::string _text;
	public:
		inline void push(char c) { _text.push_back(c); };
		inline void pop() { _text.pop_back(); };
		inline const std::string& getText() { return _text; };

		void setColour(const NormalisedColour &colour) { _colour = colour; };
		void setFont(const std::string& font);

		void render(Shader*) override;

		const std::string& operator=(const std::string& rhs) { _text = rhs; return _text; };

		UIText(float x, float y, float w, float h, unsigned char f) : UIElement(x, y, w, h, f) {};
		UIText() {};
		~UIText() { std::printf("Destroy UITEXT (%p)\n", this); };
	};
}
