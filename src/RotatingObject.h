#pragma once
#include "GameObject.h"

namespace core {

class RotatingObject :
    public GameObject
{
public:
	float _angularVelocity;

	// Inherited via GameObject
	virtual void Update() override;

	RotatingObject(float angularVelocity): _angularVelocity(angularVelocity){}

	RotatingObject(float x, float y, float angularVelocity) : RotatingObject(angularVelocity) 
	{
		SetLocalPosition(Vector2(x, y));
	}
};

}

