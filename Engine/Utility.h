#pragma once
#include "Vertex.h"
#include <glm/vec2.hpp>
#include <vector>

class String;

namespace Utility {
	glm::vec2 getOffsetOfUVIndex(int Index, int divisions);
	void sheetUV(Vertex (&vertices)[6], int index, int divisionsX, int divisionsY);
	void splitString(const String& s, char c, std::vector<String>& v);
}
