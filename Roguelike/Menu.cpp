#include "Menu.h"
#include <Engine/GUI.h>

using namespace GUI;

bool Menu::_enabled;

void Menu::init(Font &f) {
	UIContainer *root = new UIContainer(.33,.1,.33,.8,NORMALISED_HEIGHT | NORMALISED_WIDTH | NORMALISED_X | NORMALISED_Y);
	UIRect *rootrect = new UIRect(0,0,1,1,NORMALISED_WIDTH | NORMALISED_HEIGHT);

	UIContainer *titleBox = new UIContainer(0,32,1,32,NORMALISED_WIDTH | ONEMINUS_Y);
	UIRect *titleRect = new UIRect();
	UIText *title = new UIText();
	Button *qb = new Button(0, 0, 1, 32, NORMALISED_WIDTH);

	rootrect->setColour(NormalisedColour(0,0.5,0));

	titleBox->addElement(titleRect);
	titleBox->addElement(title);
	titleRect->setColour(NormalisedColour(0,0.25,0));
	*title = "MAIN MENU";
	title->setColour(NormalisedColour(1,1,1));
	title->setFont(f);

	qb->setColour(NormalisedColour(0,0.5,0));
	qb->setHoverColour(NormalisedColour(0,1,0));
	qb->label.setColour(NormalisedColour(1,0,0));
	qb->label.setFont(f);
	qb->label = "QUIT";

	root->addElement(rootrect);
	root->addElement(titleBox);
	root->addElement(qb);

	GlobalUI::add(root);
}

void Menu::render() {

}