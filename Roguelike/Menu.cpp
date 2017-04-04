#include "Menu.h"

#include "Constants.h"
#include "GameManager.h"
#include "UI.h"
#include "UIWindow.h"

#include <Engine/GUI.h>
#include <iostream>
using namespace GUI;

bool Menu::_enabled;

UIWindow *mainMenu, *options;
Window_LevelSelect *levelSelect;

void Quit_OnClick() {
	GameManager::gameInstance->stop();
}

void Level_OnClick(UIElement* caller) {
	GameManager::gameInstance->beginGame((std::string("Game/Levels/") + static_cast<UI_Button*>(caller)->label.text).c_str());
	GlobalUI::clear();
}

void Menu::init() {
	mainMenu = new UIWindow(.33f, .1f, .33f, .8f, NORMALISED_HEIGHT | NORMALISED_WIDTH | NORMALISED_X | NORMALISED_Y, "Main Menu", Constants::font, false);

	UI_Button *menu_Play = new UI_Button();
	menu_Play->addFlags(FLIPPED_Y);
	menu_Play->setHeight(-32);
	menu_Play->setY(32);
	menu_Play->label.setFont(Constants::font);
	menu_Play->label = "Play";
	menu_Play->bind_onClick(openLS);

	UI_Button *menu_Quit = new UI_Button();
	menu_Quit->label.setFont(Constants::font);
	menu_Quit->label = "Quit";
	menu_Quit->bind_onClick(Quit_OnClick);

	mainMenu->addElement(menu_Play);
	mainMenu->addElement(menu_Quit);

	////////////////////////////////////////////

	////////////////////////////////////////////
	Menu::setEnabled(true);
}

void Menu::setEnabled(bool b) {
	if (b && _enabled) return;
	_enabled = b;
	if (_enabled)
		GlobalUI::add(mainMenu);
	else GlobalUI::remove(mainMenu);
}

void Menu::openLS() {
	if (!Window_LevelSelect::status) { //Something tells me there's a better way of checking this...
		levelSelect = new Window_LevelSelect(.66f, 0, .34f, .8f, NORMALISED_HEIGHT | NORMALISED_WIDTH | NORMALISED_X | NORMALISED_Y);
		levelSelect->refresh();
		levelSelect->bind_level(Level_OnClick);
		GlobalUI::add(levelSelect);
	}
}
