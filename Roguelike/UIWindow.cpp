#include "UIWindow.h"

#include "UI.h"

using namespace GUI;

void UIWindow::CloseWindow(UIElement* closebutton) {
	delete closebutton->getParent()->getParent();
}

UIWindow::UIWindow(float x, float y, float w, float h, uByte f, const char* name, const std::string& font, bool addclosebutton) :
	UIContainer(x, y, w, h, f),
	titleBar(0, 1, 1, -32, NORMALISED_Y | NORMALISED_WIDTH),
	titleRect(0, 0, 1, 1, NORMALISED_WIDTH | NORMALISED_HEIGHT),
	titleText(0, 0, 1, 1, NORMALISED_WIDTH | NORMALISED_HEIGHT),
	closeButton(0, 0, -64, 1, NORMALISED_HEIGHT | FLIPPED_X),
	bg(0, 0, 1, 1, NORMALISED_WIDTH | NORMALISED_HEIGHT)
{
	//Title Bar

	titleRect.setColour(NormalisedColour(0, 0, 1));
	titleText.setFont(font);
	titleText.setColour(NormalisedColour(1, 1, 1));
	titleText = name;

	closeButton.setColour(NormalisedColour(1, 0, 0));
	closeButton.setHoverColour(NormalisedColour(0.25f, 0, 0));
	closeButton.label.setFont(font);
	closeButton.label.setColour(NormalisedColour(1, 1, 1));
	closeButton.label = "X";
	closeButton.bind_onClick(UIWindow::CloseWindow);

	bg.setColour(NormalisedColour(0, 0.8f, 0));

	this->addElement(bg);
	this->addElement(titleBar);
	titleBar.addElement(titleRect);
	titleBar.addElement(titleText);
	if (addclosebutton)titleBar.addElement(closeButton);
}

UIWindow::~UIWindow() {
	std::printf("Destroy UIWindow\n");
}


#include "Constants.h"
#include <Engine/IOManager.h>

bool Window_LevelSelect::status; //Hmmmm...........

Window_LevelSelect::Window_LevelSelect(float x, float y, float w, float h, unsigned char flags) : UIWindow(x, y, w, h, flags, "Level Select", Constants::font) {
	status = true;
};

void Window_LevelSelect::bind_level(void(*function)(UIElement*)) {
	for (Button* button : _buttons)
		button->bind_onClick(function);
}

void Window_LevelSelect::refresh() {
	_buttons.clear();

	std::vector<std::string> files = IOManager::getFilesInDirectory("Game/Levels", "level");

	for (int i = 0; i < files.size(); i++) {
		UI_Button* button = new UI_Button();
		button->setFlags(NORMALISED_WIDTH | FLIPPED_Y);
		button->setY(32.f * (i + 1));
		button->setHeight(-32);
		button->label.setFont(Constants::font);
		button->label = files[i];

		this->addElement(button);
		_buttons.push_back(button);
	}
}
