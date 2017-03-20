#include "Vector.h"

const Vector2f operator+( const Vector2f& a, const Vector2f& b) {
	return Vector2f {a.x + b.x, a.y + b.y};
}