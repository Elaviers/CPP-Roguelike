#pragma once
#include <Engine/Font.h>

class Menu {
private:
	static bool _enabled;

public:
	static void init();
	static void setEnabled(bool enabled);

	static void openLS();
};