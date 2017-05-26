#include "Vector2.h"

const bool operator==(const Vector2& a, const Vector2& b) {
	return a.x == b.x && a.y == b.y;
}

const Vector2 operator+(const Vector2& a, const Vector2& b) {
	return Vector2 {a.x + b.x, a.y + b.y};
}
