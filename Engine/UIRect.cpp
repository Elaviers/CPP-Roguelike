#include "UIRect.h"

#include "RenderType.h"

#include <GL/glew.h>

using namespace GUI;

void UIRect::render(Shader *s) {
	if (!s || s->Channel == RenderTypes::NONE) {
		glColor4f(_colour.r, _colour.g, _colour.b, _colour.a);
		glRectf(_min.x * 2 - 1, _min.y * 2 - 1, _max.x * 2 - 1, _max.y * 2 - 1);
	}
}