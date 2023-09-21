#pragma once
#include <math.h>
#include <vector>

#include "Drawable.h"

#include "Vector2.h"
#include "Console.h"
#include "Application.h"

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
		if (r_start._y > r_end._y) {
			ProcessVerticalLine(r_end, r_start, color);
		}
		ProcessVerticalLine(r_start, r_end,color);
		
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
		int nextY = startY + floor(float((float)x - (float)startX) * yMovement);
		//Application::GetInstance().ofstream << "x " << x << " yMovement " << yMovement << "float((float)x - (float)startX) * yMovement: )" << (float((float)x - (float)startX) * yMovement)<< " Next Y " <<nextY<< std::endl;
		ColorPixel(x, nextY, color);
	}
}

void Drawable::ProcessVerticalLine(const Vector2& r_start, const Vector2& r_end, const int color)
{
	int startY = floor(r_start._y);
	int endY = ceil(r_end._y);
	Vector2 direction = (r_end - r_start);
	float xMovement = direction.NormalizedY()._x;

	//The vector is going left or right, we must determine which horizontal segments we check, we'll only check those that are going to cross the vector
	int startX = ceil(r_start._x);
	if (r_end._x > r_start._x)
	{
		startX = floor(r_start._x);
	}
	
	//ColorPixel(startX, startY, color);
	for(int y = startY;y < endY;y++) {
		//We find on which y the collision with the next vertical line will happen
		int nextX = startX + floor(float((float)y - (float)startY) * xMovement);
		ColorPixel(nextX, y, color);
	}
}

const std::string Drawable::SORTED_BY_LUMINANCE_STRING="`.-':_,^=;><+!rc*/z?sLTv)J7(|Fi{C}fI31tlu[neoZ5Yxjya]2ESwqkP6h9d4VpOGbUAKXHm8RD#$Bg0MNWQ%&@█";

void Drawable::ColorPixel(const int x,const int y,const int color,const float proportion,const float alpha) {
	Console& r_console = Console::GetInstance();

	int charToUseIndex=std::floor(proportion*(SORTED_BY_LUMINANCE_STRING.length()-1));
	//We can't use char because the white square █ doesn't fit in a char
	int charToUse=SORTED_BY_LUMINANCE_STRING.at(charToUseIndex);

	//Picking the white square from the string doesnt work, I don't know why
	if(proportion==1)
	{
		charToUse=0x2588;
	}
	
	r_console._virtual_buffer[x][y].Char.UnicodeChar = charToUse;
	r_console._virtual_buffer[x][y].Attributes = color;
}

