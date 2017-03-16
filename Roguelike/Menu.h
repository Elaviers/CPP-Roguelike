#include <Engine/UIPrimitives.h>

class Menu {
private:
	static bool _enabled;
public:
	static void init(Font&);
	static void setEnabled(bool enabled);
	static void render();
};