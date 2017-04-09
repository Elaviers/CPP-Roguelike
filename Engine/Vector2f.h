#pragma once
#include "Vector2.h"

struct Vector2f { 
	float x, y;

	operator Vector2() const;
};

const bool operator==(const Vector2f& a, const Vector2f& b);
const bool operator!=(const Vector2f& a, const Vector2f& b);

const Vector2f operator+(const Vector2f& a, const Vector2f& b);
