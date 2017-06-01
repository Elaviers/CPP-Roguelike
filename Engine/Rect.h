#pragma once
#include "Vector2.h"

template <class T>
struct Rect {
	Rect() {};
	Rect(const Vector2<T>& min, const Vector2<T>& max) : min(min), max(max) {};
	~Rect() {};

	Vector2<T> min, max;
};

typedef Rect<float> Rect_f;
typedef Rect<int> Rect_i;
