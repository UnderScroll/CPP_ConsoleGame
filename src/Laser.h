#pragma once
#include <vector>

#include "Polygon.h"
#include "Collider.h"
#include "Ray.h"

namespace core {

class Laser 
	: public GameObject
{
public:
	Laser(Vector2 position = Vector2(0, 0), Vector2 direction = Vector2(0, 0));

	Vector2 _position;
	Vector2 _direction;

	Polygon _laserBase;
	Polygon _laserBeam;

	void computeBeam(std::vector<Collider>& colliders);

	virtual void Update();
	virtual void Draw();
private:
	void computeBeamRec(std::vector<Collider>& colliders, Ray& ray, unsigned int nb_iter);
};

}
