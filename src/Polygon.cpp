#include "Polygon.h"
#include <cmath>

void Polygon::Draw()
{
	for (int i = 0;i < _points.size();++i) {
		Vector2 currentPoint = _position + _points[i];
		Vector2 nextPoint = _position + _points[(i<_points.size()-1)?i + 1:0];
		
		Drawable::ProcessLine(currentPoint, nextPoint,color);
	}
}
