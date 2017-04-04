#pragma once

class Menu {
private:
	static bool _enabled;

public:
	static void init();
	static void setEnabled(bool enabled);

	static void openLS();
};
