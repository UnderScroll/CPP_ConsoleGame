#include "Polygon.h"
#include <cmath>
#define INF <
#define SUP >

void Polygon::Draw(Console& r_cons)
{
	for (int i = 0;i < _points.size() - 1;++i) {
		Vector2 currentPoint = _position + _points[i];
		Vector2 nextPoint = _position + _points[i + 1];
		Vector2 direction = nextPoint-currentPoint;

		
		std::vector<int> segmentsToCheckY[];
		if(std::abs(direction._x)>std::abs(direction._y))
		{
			std::vector<int> segmentsToCheckY[];
			
			int bornMinX=currentPoint._x;
			int bornMaxX=nextPoint._x;

			//The vector is going left or right, we must determine which horizontal segments we check, we'll only check those that are going to cross the vector
			int bornMinY=ceil(currentPoint._y);
			int bornMaxY=floor(nextPoint._y);
			if(direction._y<0)
			{
				bornMinY=floor(currentPoint._y);
				bornMaxY=ceil(nextPoint._y);
			}
			
		}else
		{
			//The vector is going up or down, we must determine which segments to check on the x axis, we'll only check those that are going to cross the vector
			int bornMinX=ceil(currentPoint._x);
			int bornMaxX=floor(nextPoint._x);
			if(direction._x<0)
			{
				bornMinX=floor(currentPoint._x);
				bornMaxX=ceil(nextPoint._x);
			}
		}

	}
}
