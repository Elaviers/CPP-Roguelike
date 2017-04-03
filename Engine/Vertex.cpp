#include "Vertex.h"

bool Colour::operator!=(const Colour& other) {
	return (r != other.r || g != other.g || b != other.b || a != other.a);
}
