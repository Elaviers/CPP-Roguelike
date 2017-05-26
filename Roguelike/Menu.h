#pragma once

class Menu { //this is stupid
private:
	static bool _enabled;

public:
	static void init();
	static void setEnabled(bool enabled);

	static void openLS();
};
