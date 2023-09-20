#pragma once
#include <math.h>
#include <vector>

#include "Drawable.h"

#include "Vector2.h"
#include "Console.h"

void Drawable::ProcessLine(const Vector2& r_start, const Vector2& r_end, const int color)
{
	Vector2 direction = r_end - r_start;
	std::vector<int> segmentsToCheckY;
	if (std::abs(direction._x) > std::abs(direction._y))
	{
		if (r_start._x > r_end._x) {
			ProcessHorizontalLine(r_end, r_start, color);
		}
		ProcessHorizontalLine(r_start, r_end,color);
		
	}
	else
	{
		//The vector is going up or down, we must determine which segments to check on the x axis, we'll only check those that are going to cross the vector
		int bornMinX = ceil(r_start._x);
		int bornMaxX = floor(r_end._x);
		if (direction._x < 0)
		{
			bornMinX = floor(r_start._x);
			bornMaxX = ceil(r_end._x);
		}
	}
}

void Drawable::ProcessHorizontalLine(const Vector2& r_start, const Vector2& r_end, const int color)
{
	int startX = floor(r_start._x);
	int endX = ceil(r_end._x);
	Vector2 direction = (r_end - r_start);
	float yMovement = direction.NormalizedX()._y;

	//The vector is going left or right, we must determine which horizontal segments we check, we'll only check those that are going to cross the vector
	int startY = ceil(r_start._y);
	if (r_end._y > r_start._y)
	{
		startY = floor(r_start._y);
	}
	
	//ColorPixel(startX, startY, color);
	for(int x = startX;x < endX;x++) {
		//We find on which y the collision with the next vertical line will happen
		int nextY = startY + floor((x - startX) * yMovement);
		ColorPixel(x, nextY, color);
	}
}

void Drawable::ProcessVerticalLine(const Vector2& r_start, const Vector2& r_end, const int color)
{

}

void Drawable::ColorPixel(const int x,const int y,const int color,float proportion=1, float alpha=1) {
	Console& r_console = Console::GetInstance();
}
