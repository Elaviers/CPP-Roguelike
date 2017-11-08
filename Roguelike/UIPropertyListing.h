#pragma once
#include <Engine/UIContainer.h>
#include <Engine/UIRect.h>
#include <Engine/UIText.h>
#include <Engine/UITextbox.h>

class UIPropertyListing : public UIContainer
{
public:
	UIPropertyListing(float x, float y, float w, float h, unsigned char f);
	virtual ~UIPropertyListing() {};

	UIRect rect;
	UIText text;
	UITextBox textBox;
};

