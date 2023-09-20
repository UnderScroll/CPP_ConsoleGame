#pragma once
#include "Drawable.h"
#include "Vector2.h"
#include <math.h>

void Drawable::ProcessLine(Console& console, Vector2 start, Vector2 end)
{
	Vector2 direction = end - start;
	if(direction._x>0 )
}

void Drawable::ProcessHorizontalLine(Console& console, Vector2 start, Vector2 end)
{
}

void Drawable::ProcessVerticalLine(Console& console, Vector2 start, Vector2 end)
{
}
