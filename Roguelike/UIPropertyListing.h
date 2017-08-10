#pragma once
#include <Engine/UIContainer.h>
#include <Engine/UIRect.h>
#include <Engine/UIText.h>
#include <Engine/Textbox.h>

class UIPropertyListing : public GUI::UIContainer
{
public:
	UIPropertyListing(float x, float y, float w, float h, unsigned char f);
	virtual ~UIPropertyListing() {};

	GUI::UIRect rect;
	GUI::UIText text;
	GUI::TextBox textBox;
};

