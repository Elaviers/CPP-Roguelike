#include "UIWindow.h"
#include "UI.h"

using namespace GUI;



UIWindow::UIWindow(float x,float y,float w,float h,unsigned char f, const char* name, const std::string& font) : UIContainer(x,y,w,h,f) {
	//Title Bar
	titleBar = new GUI::UIContainer(0,1,1,-32,NORMALISED_Y | NORMALISED_WIDTH);
		titleRect = new GUI::UIRect(0,0,1,1,NORMALISED_WIDTH | NORMALISED_HEIGHT);
		titleText = new GUI::UIText(0, 0, 1, 1, NORMALISED_WIDTH | NORMALISED_HEIGHT);
		closeButton = new GUI::Button(0, 0, -64, 1, NORMALISED_HEIGHT | FLIPPED_X);
	bg = new GUI::UIRect(0,0,1, 1, NORMALISED_WIDTH | NORMALISED_HEIGHT);

	titleRect->setColour(NormalisedColour(0,0,1));
	titleText->setFont(font);
	titleText->setColour(NormalisedColour(1,1,1));
	titleText->text = name;

	closeButton->setColour(NormalisedColour(1,0,0));
	closeButton->setHoverColour(NormalisedColour(0.25f,0,0));
	closeButton->label.setFont(font);
	closeButton->label.setColour(NormalisedColour(1,1,1));
	closeButton->label = "X";

	bg->setColour(NormalisedColour(0,0.8f,0));

	this->addElement(bg);
	this->addElement(titleBar);
	titleBar->addElement(titleRect);
	titleBar->addElement(titleText);
	titleBar->addElement(closeButton);
}


UIWindow::~UIWindow() {
	std::printf("Destroy UIWindow\n");
}
