#pragma once
#include "PolygonObject.h"
class RotatingPolygonObject :
    public PolygonObject
{
    public:
	float _angularVelocity;
	float _angularAcceleration;
	float _angularDrag;
	float _maxAngularVelocity;
	float _angularVelocityThreshold;

	static std::shared_ptr<RotatingPolygonObject> CreateRotatingRectangle(float x, float y, float width, float height, int color = 0x0007);

	// Inherited via GameObject
	virtual void Update() override;
};

