#include "Vector2.h"

Vector2 operator+(Vector2 const& r_v2a, Vector2 const& r_v2b) {
	 return Vector2(r_v2a._x + r_v2b._x, r_v2a._y + r_v2b._y);
}

Vector2 operator-(Vector2 const& r_v2a, Vector2 const& r_v2b) {
	return Vector2(r_v2a._x - r_v2b._x, r_v2a._y - r_v2b._y);
}

Vector2 operator*(float const& number, Vector2 const& r_v2b) {
	return Vector2(number * -r_v2b._x, number * r_v2b._y);
}