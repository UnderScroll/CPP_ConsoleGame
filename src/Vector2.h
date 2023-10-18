#pragma once
#include <cmath>

#define PI_F 3.14159265358979f
#define RAD_TO_DEG (180/PI_F)
#define DEG_TO_RAD (PI_F/180)

namespace core {

	class Vector2
	{
	private:
		double _magnitude;

	public:
		Vector2(double x, double y) {
			_x = x;
			_y = y;
			_magnitude = -1;
		}

		Vector2() :Vector2(0, 0) {};

		double _x;
		double _y;

		double SqrMagnitude() {
			return this->_x * this->_x + this->_y * this->_y;
		}

		double Magnitude() {
			if (_magnitude < 0) {
				_magnitude = sqrt(SqrMagnitude());
			}
			return _magnitude;
		}

		Vector2 Normalized() {
			double magnitude = Magnitude();
			return Vector2(this->_x / magnitude, this->_y / magnitude);
		}

		//Return a version where x = 1 or -1
		Vector2 NormalizedX() {
			double abs_x = abs(_x);
			return Vector2(_x / abs_x, this->_y / abs_x);
		}

		//Return a version where y = 1 or -1
		Vector2 NormalizedY() {
			double abs_y = abs(_y);
			return Vector2(_x / abs_y, _y / abs_y);
		}

		Vector2 RotateByRadians(double angle, Vector2 center = Vector2(0, 0)) const;

		bool operator==(const Vector2& other) const;

		Vector2 RotateByDegrees(double angle, Vector2 center = Vector2(0, 0)) const
		{
			return RotateByRadians(angle * DEG_TO_RAD);
		}

		double dot(Vector2 other) const {
			return _x * other._x + _y * other._y;
		}
	};

	Vector2 operator+(Vector2 const& r_v2a, Vector2 const& r_v2b);

	Vector2 operator+=(Vector2& r_v2a, Vector2 const& r_v2b);

	Vector2 operator-(Vector2 const& r_v2a, Vector2 const& r_v2b);

	Vector2 operator*(double const& number, Vector2 const& r_v2b);

	Vector2 operator*(Vector2 const& r_v2a, double const& number);

	Vector2 operator*(Vector2 const& r_v2a, Vector2 const& r_v2b);

	double distSqrd(Vector2 a, Vector2 b);
}
