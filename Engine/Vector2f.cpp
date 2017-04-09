#include "Vector2f.h"

Vector2f::operator Vector2() const {
	return Vector2{ (int)(x < 0 ? x - 0.5f : x + 0.5f) , (int)(y < 0 ? y - 0.5f : y + 0.5f) };
}

const bool operator==(const Vector2f& a, const Vector2f& b) {
	return a.x == b.x && a.y == b.y;
}

const bool operator!=(const Vector2f& a, const Vector2f& b) {
	return a.x != b.x || a.y != b.y;
}

const Vector2f operator+(const Vector2f& a, const Vector2f& b) {
	return Vector2f{ a.x + b.x, a.y + b.y };
}
