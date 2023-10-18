#pragma once
#include "GameObject.h"

namespace core {

class RotatingObject :
    public GameObject
{
public:
	double _angularVelocity;

	// Inherited via GameObject
	virtual void Update() override;

	RotatingObject(double angularVelocity): _angularVelocity(angularVelocity){}

	RotatingObject(double x, double y, double angularVelocity) : RotatingObject(angularVelocity) 
	{
		SetLocalPosition(Vector2(x, y));
	}
};

}

