#pragma once
#include "String.h"
#include "NormalisedColour.h"
#include "UIElement.h"

//I don't want to include this here but whatever, it can stay for now
#include <stdio.h>

class Font;
class Shader;

class UIText : public UIElement
	{
		NormalisedColour	_colour;
		Font*				_font;
		String				_text;
	public:
		inline void push(char c) { _text += c; };
		inline void pop() { --_text; };
		inline void setText(const String& text) { _text = text; }
		inline const String& getText() { return _text; };

		void setColour(const NormalisedColour &colour) { _colour = colour; };
		void setFont(const char* font_path);

		void render(Shader*) override;

		UIText(float x, float y, float w, float h, unsigned char f) : UIElement(x, y, w, h, f) {};
		UIText() {};
		~UIText() { printf("Destroy UITEXT (%p)\n", this); };
};
