#include "Menu.h"
#include "UI.h"
#include "GameManager.h"
#include "UIWindow.h"
#include "Constants.h"

#include <Engine/IOManager.h>
#include <iostream>
using namespace GUI;

bool Menu::_enabled;

UIWindow *mainMenu, *levelSelect, *options;

void Quit_OnClick() {
	GameManager::gameInstance->stop();
}

void Level_OnClick(UIElement* caller) {
	GameManager::gameInstance->beginGame((std::string("Game/Levels/") + dynamic_cast<UI_Button*>(caller)->label.text).c_str());
	GlobalUI::deleteElement(mainMenu);
	GlobalUI::deleteElement(levelSelect);
}

void closeWindow(UIElement* button) {
	UIWindow* window = dynamic_cast<UIWindow*>(button->getParent()->getParent());
	if (window != nullptr)GlobalUI::remove(window);
}

void Menu::init() {
	mainMenu = new UIWindow(.33f, .1f, .33f, .8f, NORMALISED_HEIGHT | NORMALISED_WIDTH | NORMALISED_X | NORMALISED_Y, "Main Menu", Constants::font);
	mainMenu->bind_close(closeWindow);

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

	levelSelect = new UIWindow(.66f, 0, .34f, 1, NORMALISED_HEIGHT | NORMALISED_WIDTH | NORMALISED_X | NORMALISED_Y, "Level Select", Constants::font);
	levelSelect->bind_close(closeWindow);

	std::vector<std::string> files = IOManager::getFilesInDirectory("Game/Levels", "level");
	for (int i = 0; i < files.size(); i++) {
		UI_Button *button = new UI_Button();
		button->setFlags(NORMALISED_WIDTH | FLIPPED_Y);
		button->setY(32.f + 16.f * i);
		button->setHeight(-16);
		button->label.setFont(Constants::font);
		button->label = files[i];
		button->bind_onClick(Level_OnClick);

		levelSelect->addElement(button);
	}

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
	GlobalUI::add(levelSelect);
}
