#pragma once
#include <cmath>

class Vector2
{
private:
	float _magnitude;

public:
	Vector2(float x, float y) {
		_x = x;
		_y = y;
		_magnitude = -1;
	}

	Vector2() :Vector2(0, 0) {};

	float _x;
	float _y;


	float Magnitude() {
		if (_magnitude < 0) {
			_magnitude = sqrt(this->_x * this->_x + this->_y * this->_y);
		}
		return _magnitude;
	}

	Vector2 Normalized() {
		float magnitude = Magnitude();
		return Vector2(this->_x / magnitude, this->_y / magnitude);
	}

	//Return a version where x = 1 or -1
	Vector2 NormalizedX() {
		float abs_x = abs(_x);
		return Vector2(_x / abs_x, this->_y / abs_x);
	}


	//Return a version where y = 1 or -1
	Vector2 NormalizedY() {
		float abs_y = abs(_y);
		return Vector2(_x / abs_y,_y / abs_y);
	}
};

Vector2 operator+(Vector2 const& r_v2a, Vector2 const& r_v2b);

Vector2 operator-(Vector2 const& r_v2a, Vector2 const& r_v2b);

Vector2 operator*(float const& number, Vector2 const& r_v2b);
