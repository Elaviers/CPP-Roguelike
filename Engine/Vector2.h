#pragma once

struct Vector2 { 
	int x, y;
};

const bool operator==(const Vector2& a, const Vector2& b);

const Vector2& operator+ (const Vector2& a, const Vector2& b);
