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
	bool _isClosed;

	virtual Vector2 GetBoundingBox() override;
	virtual double GetDiameter() override;

	virtual void Draw() override;
	void RotateToRadians(double targetAngle);

    virtual void SetLocalScale(Vector2 targetScale) override;

	virtual void Update() override {}

	Polygon(): _isClosed(true) {
		_color = WHITE;
	};

	Polygon(std::vector<Vector2> points, bool isClosed, Color color = WHITE, double alpha = 1, Vector2 localPosition = Vector2(0, 0), Vector2 localScale = Vector2(1, 1), double localRotation=0) :_points(points),
	 _isClosed(isClosed)
	{
		_alpha = alpha;
		_color = color;
		_localPosition = localPosition;
		_localScale = localScale;
		_localRotation = localRotation;

		ComputePoints();
	};

	void OnCreationOver() override;
	void ComputePoints();

	std::vector<Vector2> _computedPointsWorldPositions;

	std::vector<Vector2> _computedPoints;
};

}
