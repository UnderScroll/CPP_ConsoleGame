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

Vector2 operator+(Vector2 const& r_v2a, Vector2 const& r_v2b);

Vector2 operator-(Vector2 const& r_v2a, Vector2 const& r_v2b);

Vector2 operator*(float const& number, Vector2 const& r_v2b);
