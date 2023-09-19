#include "Polygon.h"

void Polygon::Draw(Console& r_cons)
{
	for (int i = 0;i < _points.size() - 1;++i) {
		Vector2 currentPoint = _position + _points[i];
		Vector2 nextPoint = _position + _points[i + 1];
		Vector2 direction = nextPoint-currentPoint;


	}
}
