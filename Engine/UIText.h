#pragma once
#include "NormalisedColour.h"
#include "UIElement.h"

#include <string>

class Font;
class Shader;

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
		inline void setText(const std::string& text) { _text = text; }
		inline const std::string& getText() { return _text; };

		void setColour(const NormalisedColour &colour) { _colour = colour; };
		void setFont(const std::string& font);

		void render(Shader*) override;

		const std::string& operator=(const std::string& rhs) { _text = rhs; return _text; }; //This is dumb

		UIText(float x, float y, float w, float h, unsigned char f) : UIElement(x, y, w, h, f) {};
		UIText() {};
		~UIText() { std::printf("Destroy UITEXT (%p)\n", this); };
	};
}
