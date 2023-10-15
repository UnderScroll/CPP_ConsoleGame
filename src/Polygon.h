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
	Color _color;
	float _alpha;
	bool _isClosed;

	Vector2 GetBoundingBox();
	float GetDiameter();

	virtual void Draw() override;
	void RotateToRadians(float targetAngle);

    virtual void SetLocalScale(Vector2 targetScale) override;

	virtual void Update() override {}

	Polygon(): _alpha(1), _color(WHITE), _isClosed(true) {};

	Polygon(std::vector<Vector2> points, bool isClosed, Color color = WHITE, float alpha = 1, Vector2 localPosition = Vector2(0, 0), Vector2 localScale = Vector2(1, 1)) :_points(points), _color(color),
		_alpha(alpha), _isClosed(isClosed), _computedPoints(_points)
	{
		_localPosition = localPosition;
		_localScale = localScale;
	};

	void OnCreationOver() override;
protected:
    std::vector<Vector2> _computedPoints;
    void ComputePoints();
};

}
