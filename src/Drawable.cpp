#pragma once
#include <math.h>
#include <vector>

#include "Drawable.h"

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

	float luminancesCache[Console::WIDTH/2][Console::HEIGHT]={0};
	
	for(int x = startX;x < endX;x++) {
		//We find on which y the collision with the next vertical line will happen
		float nextY = startY + (float)(x - startX) * yMovement;

		//We apply the principles of Xiaolin Wu's algorithm to calculate the luminance of the two pixels to place
		//https://www.geeksforgeeks.org/anti-aliased-line-xiaolin-wus-algorithm/
		float decimalPartOfY=nextY-floor(nextY);

		int inextY=floor(nextY);
		luminancesCache[x][inextY]+=1-decimalPartOfY;
		luminancesCache[x][inextY-1]+=decimalPartOfY;
		
		ColorPixel(x, inextY, color,luminancesCache[x][inextY]);
		ColorPixel(x, inextY-1, color,luminancesCache[x][inextY-1]);
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

	float luminancesCache[Console::WIDTH/2][Console::HEIGHT]={0};
	
	for(int y = startY;y < endY;y++) {
		//We find on which y the collision with the next vertical line will happen
		float nextX = startX + (float)(y - startY) * xMovement;

		//We apply the principles of Xiaolin Wu's algorithm to calculate the luminance of the two pixels to place
		//https://www.geeksforgeeks.org/anti-aliased-line-xiaolin-wus-algorithm/
		float decimalPartOfX=nextX-floor(nextX);

		int inextX=floor(nextX);
		luminancesCache[inextX][y]+=1-decimalPartOfX;
		luminancesCache[inextX+1][y]+=decimalPartOfX;
		
		ColorPixel(inextX, y, color,luminancesCache[inextX][y]);
		ColorPixel(inextX+1, y, color,luminancesCache[inextX+1][y]);
	}
	
	//ColorPixel(startX, startY, color);
	for(int y = startY; y < endY; y++) {
		//We find on which y the collision with the next vertical line will happen
		int nextX = startX + floor(float((float)y - (float)startY) * xMovement);
		ColorPixel(nextX, y, color);
	}
}

const std::string Drawable::SORTED_BY_LUMINANCE_STRING="`.-':_,^=;><+!rc*/z?sLTv)J7(|Fi{C}fI31tlu[neoZ5Yxjya]2ESwqkP6h9d4VpOGbUAKXHm8RD#$Bg0MNWQ%&@";

void Drawable::ColorPixel(const int x,const int y,const int color,const float proportion,const float alpha) {
	if(x < 0 || y < 0) return;
	Console& r_console = Console::GetInstance();

	int charToUseIndex=std::floor(proportion*(SORTED_BY_LUMINANCE_STRING.length()-1));
	int charToUse=SORTED_BY_LUMINANCE_STRING.at(charToUseIndex);
	
	r_console._virtual_buffer[x][y].Char.UnicodeChar = charToUse;
	r_console._virtual_buffer[x][y].Attributes = color;
}

