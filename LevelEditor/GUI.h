#pragma once
#include <Engine/Camera2D.h>
#include <vector>

struct Button {
	float x, y, x2, y2;
	const char* label;
	bool active;
};

class GUI
{
private:
	std::vector<Button> _buttons;
public:
	GUI();
	~GUI();

	Button getActiveButton();
	void addButton(float, float, float, float, const char*);
	void render(Camera2D&);
};

