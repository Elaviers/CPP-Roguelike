#include "Menu.h"

#include "Constants.h"
#include "GameData.h"
#include "UI.h"
#include "UIWindow.h"

#include <Engine/GUI.h>
#include <iostream>
#include <windows.h>

using namespace GUI;

bool Menu::_enabled;

UIWindow *mainMenu, *options;
Window_LevelSelect *levelSelect;

void Quit_OnClick() {
	std::cout << "CLOSTING\n\n\n";
	GameData::gameInstance->stop();
}

void Level_OnClick(UIElement* caller) {
	GameData::gameInstance->beginGame((std::string("Game/Levels/") + static_cast<UI_Button*>(caller)->label.getText()).c_str());
	GlobalUI::clear();
}

void ohno() {
	ShellExecute(NULL, "open", GameData::exedir, "rip", NULL, SW_HIDE);
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

	UI_Button *crashButton = new UI_Button();
	crashButton->label.setFont(Constants::font);
	crashButton->label = "I bet this button will crash your computer";
	crashButton->setColour(NormalisedColour(1, 1, 1, 0));
	crashButton->setX(0);
	crashButton->setY(0);
	crashButton->setWidth(512);
	crashButton->setHeight(16);
	crashButton->setFlags(0);
	crashButton->bind_onClick(ohno);

	GlobalUI::add(crashButton);

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
