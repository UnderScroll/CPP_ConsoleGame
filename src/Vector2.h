#pragma once
class Vector2
{
public:
	Vector2(float x, float y) {
		_x = x;
		_y = y;
	}

	Vector2() :Vector2(0, 0) {};

	float _x;
	float _y;

};

Vector2 operator+(Vector2 const& r_v2a, Vector2 const& r_v2b) {
	return Vector2(r_v2a._x + r_v2b._x, r_v2a._y + r_v2b._y);
}

Vector2 operator-(Vector2 const& r_v2a, Vector2 const& r_v2b) {
	return Vector2(r_v2a._x - r_v2b._x, r_v2a._y - r_v2b._y);
}

Vector2 operator*(float const& number, Vector2 const& r_v2b) {
	return Vector2(number* - r_v2b._x, number* r_v2b._y);
}
