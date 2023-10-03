#pragma once
#include "GameObject.h"

class RotatingObject :
    public GameObject
{
public:
	float _angularVelocity;
	
	static std::shared_ptr<RotatingObject> CreateRotatingObject(float x, float y, float angularVelocity, std::shared_ptr<GameObject> r_child);

	// Inherited via GameObject
	virtual void Update() override;

protected:
	RotatingObject(float angularVelocity): _angularVelocity(angularVelocity){}
};

