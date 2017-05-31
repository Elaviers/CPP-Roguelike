#pragma once

template<class T>
struct Vector2
{
	T x, y;

	Vector2() : x(0), y(0) {};
	Vector2(const T& x, const T& y) : x(x), y(y) {};
	~Vector2() {};

	template <class O>
	inline operator Vector2<O>() { return Vector2<O>((O)x, (O)y); }

	inline const bool operator==(const Vector2& other) const { return x == other.x && y == other.y; };
	inline const bool operator!=(const Vector2& other) const { return x != other.x || y != other.y; };
	inline const Vector2 operator +(const Vector2& other) const { return Vector2(x + other.x, y + other.y); };
};

typedef Vector2<float> Vector2f;
typedef Vector2<int> Vector2i;
