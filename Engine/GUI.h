#pragma once
#include "UIContainer.h"

class GlobalUI {
private:
	static UIContainer _root;
	static std::vector<UIElement*> _elementsToDelete;
public:
	static void clear(); //Careful!
	static bool update(int mouseX, int mouseY);
	static void add(UIElement&);
	static void add(UIElement*);
	static void remove(UIElement*);
	static void deleteElement(UIElement*); //marks this element and all children to be deleted next time update is called
	static void setCameraSize(int, int);
	static void render(Shader*);
	static void click();
};
