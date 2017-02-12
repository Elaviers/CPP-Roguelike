#include <Engine/UIPrimitives.h>

class Menu {
private:
	static bool _enabled;
public:
	static void init(Font&);
	static void setEnabled(bool enabled) { _enabled = enabled; };
	static void render();
};