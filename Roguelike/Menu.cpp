#include "Menu.h"
#include <Engine/GUI.h>
#include "GameManager.h"

using namespace GUI;

bool Menu::_enabled;

UIContainer* root;

void Quit_OnClick() {
	GameManager::gameInstance->stop();
}

void Play_OnClick() {
	Menu::setEnabled(false);
	GameManager::gameInstance->beginGame();
}

void Menu::init(Font &f) {
	root = new UIContainer(.33,.1,.33,.8,NORMALISED_HEIGHT | NORMALISED_WIDTH | NORMALISED_X | NORMALISED_Y);
	UIRect *rootrect = new UIRect(0,0,1,1,NORMALISED_WIDTH | NORMALISED_HEIGHT);

	UIContainer *titleBox = new UIContainer(0,0,1,32,NORMALISED_WIDTH | ONEMINUS_Y);
	UIRect *titleRect = new UIRect();
	UIText *title = new UIText();
	Button *playButton = new Button(0, 32, 1, 32, NORMALISED_WIDTH | ONEMINUS_Y);
	Button *qb = new Button(0, 0, 1, 32, NORMALISED_WIDTH);

	rootrect->setColour(NormalisedColour(0,0.5,0));

	titleBox->addElement(titleRect);
	titleBox->addElement(title);
	titleRect->setColour(NormalisedColour(0,0.25,0));
	*title = "MAIN MENU";
	title->setColour(NormalisedColour(1,1,1));
	title->setFont(f);

	playButton->setColour(NormalisedColour(0, 0.5, 0));
	playButton->setHoverColour(NormalisedColour(0, 1, 0));
	playButton->label.setColour(NormalisedColour(1,0,0));
	playButton->label.setFont(f);
	playButton->label = "PLAY";
	playButton->onClick = Play_OnClick;

	qb->setColour(NormalisedColour(0,0.5,0));
	qb->setHoverColour(NormalisedColour(0,1,0));
	qb->label.setColour(NormalisedColour(1,0,0));
	qb->label.setFont(f);
	qb->label = "QUIT";
	qb->onClick = Quit_OnClick;

	root->addElement(rootrect);
	root->addElement(titleBox);
	root->addElement(playButton);
	root->addElement(qb);

	Menu::setEnabled(true);
}

void Menu::setEnabled(bool b) {
	if (b && _enabled) return;
	_enabled = b;
	if (_enabled)
		GlobalUI::add(root);
	else GlobalUI::remove(root);
}

void Menu::render() {

}