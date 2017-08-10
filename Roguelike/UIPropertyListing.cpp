#include "UIPropertyListing.h"

#include "Constants.h"

using namespace GUI;

UIPropertyListing::UIPropertyListing(float x, float y, float w, float h, unsigned char f) :
	UIContainer(x, y, w, h, f),
	rect(0, 0, .5f, 1, NORMALISED_WIDTH | NORMALISED_HEIGHT),
	text(0, 0, .5f, 1, NORMALISED_WIDTH | NORMALISED_HEIGHT),
	textBox(0.5f, 0, .5f, 1, NORMALISED_X | NORMALISED_WIDTH | NORMALISED_HEIGHT)
{
	addElement(rect);
	addElement(text);
	addElement(textBox);

	rect.setColour(NormalisedColour(.25f,.25f,.25f));
	textBox.setColour(NormalisedColour(0, 0, .75f));
	textBox.setSelectColour(NormalisedColour(0, 0, .25f));

	text.setFont(Constants::font_editor);
	textBox.label.setFont(Constants::font_editor);
}
