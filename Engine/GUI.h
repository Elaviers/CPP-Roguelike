#pragma once
#include "UIContainer.h"

class GlobalUI {
private:
	static GUI::UIContainer _root;
	static std::vector<GUI::UIElement*> _elementsToDelete;
public:
	static void clear(); //Careful!
	static bool update(int mouseX, int mouseY);
	static void add(GUI::UIElement&);
	static void add(GUI::UIElement*);
	static void remove(GUI::UIElement*);
	static void deleteElement(GUI::UIElement*); //marks this element and all children to be deleted next time update is called
	static void setCameraSize(int, int);
	static void render(Shader*);
	static void click();
};
