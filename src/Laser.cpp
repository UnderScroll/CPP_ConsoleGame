#include "Laser.h"

#include <vector>
#include <numbers>

Laser::Laser()
	: size(10)
{
	Laser(size);
}

Laser::Laser(const float size)
	: size(size) 
{
	std::vector<Vector2> basePoints(0);
	for (unsigned int i = 0; i < 3; ++i) {
		Vector2 point = Vector2(size * cos(std::numbers::pi * 2 * i / 3.0), size * sin(std::numbers::pi * 2 * i / 3.0));
		basePoints.push_back(point);
	}

	laserBase = PolygonObject::CreatePolygon(basePoints,true,color);
	laserLine = PolygonObject::CreatePolygon({},false, 4);
}

void Laser::Update() {
	ComputeLaserLine();
	laserBase->RotateToRadians(_rotation);
	laserBase->MoveTo(_position);
	laserLine->RotateToRadians(0);
}

//WIP
void Laser::ComputeLaserLine() {
	Vector2 originPoint = laserBase->_points[0].RotateByRadians(_rotation);
	laserLine->_points = { _position, _position + originPoint };
}

void Laser::Draw() {
	
	laserBase->Draw();
	laserLine->Draw();
	Drawable::ColorPixel(_position._x, _position._y, 4);
}