#pragma once
#include <vector>

#include "GameObject.h"
#include "Vector2.h"

namespace core {

class Polygon :
	public GameObject
{
public:
	std::vector<Vector2> _points; //Coordinates are relatives to the position of the GameObject
	int _color;
	float _alpha;
	bool _isClosed;

	virtual void Draw() override;
	void RotateToRadians(float targetAngle);

    virtual void SetLocalScale(Vector2 targetScale) override;

	virtual void Update() override {}

	Polygon(): _alpha(1), _color(0), _isClosed(false) {};

	Polygon(std::vector<Vector2> points, bool isClosed, int color=0x0007, float alpha=1) :_points(points), _color(color),
		_alpha(alpha), _isClosed(isClosed), _rotated_points(_points) {}
protected:
    std::vector<Vector2> _computedPoints;
    void ComputePoints();
};

}
