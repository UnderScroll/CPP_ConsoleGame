#pragma once
#include "Drawable.h"

#include <math.h>
#include <vector>

#include "Console.h"

namespace core {

	const Drawable::Layer Drawable::LAYERS[] = { BACKGROUND,WORLD,UI };
void Drawable::DrawLine(const Vector2& r_start, const Vector2& r_end, const int color, const float alpha)
{
	Vector2 direction = r_end - r_start;
	std::vector<int> segmentsToCheckY;
	if (std::abs(direction._x) > std::abs(direction._y))
	{
		if (r_start._x > r_end._x) {
			ProcessHorizontalLine(r_end, r_start, color,alpha);
		}
		ProcessHorizontalLine(r_start, r_end,color,alpha);
	}
	else
	{
		if (r_start._y > r_end._y) {
			ProcessVerticalLine(r_end, r_start, color,alpha);
		}
		ProcessVerticalLine(r_start, r_end,color,alpha);
		
	}
}

void Drawable::ProcessHorizontalLine(const Vector2& r_start, const Vector2& r_end, const int color, const float alpha)
{
	int startX = (int)floor(r_start._x);
	int endX = (int)ceil(r_end._x);
	Vector2 direction = (r_end - r_start);
	float yMovement = direction.NormalizedX()._y;

	//The vector is going left or right, we must determine which horizontal segments we check, we'll only check those that are going to cross the vector
	int startY = (int)ceil(r_start._y);
	if (r_end._y > r_start._y)
	{
		startY = (int)floor(r_start._y);
	}

	float luminancesCache[WIDTH][HEIGHT]={0};
	
	for(int x = startX;x < endX;x++) {
		//We find on which y the collision with the next vertical line will happen
		float nextY = (float)startY + (float)(x - startX) * yMovement;

		//We apply the principles of Xiaolin Wu's algorithm to calculate the luminance of the two pixels to place
		//https://www.geeksforgeeks.org/anti-aliased-line-xiaolin-wus-algorithm/
		float decimalPartOfY=nextY-floor(nextY);

		int inextY=(int)floor(nextY);

		if (inextY < 0) continue;
		if (inextY >= HEIGHT - 1) continue;
		if (x >= WIDTH - 1) continue;
		if (x < 0) continue;

		luminancesCache[x][inextY]+=1-decimalPartOfY;
		luminancesCache[x][inextY+1]+=decimalPartOfY;
		
		ColorPixel(x, inextY, color,alpha*luminancesCache[x][inextY]);
		ColorPixel(x, inextY+1, color,alpha*luminancesCache[x][inextY+1]);
	}
}

void Drawable::ProcessVerticalLine(const Vector2& r_start, const Vector2& r_end, const int color, const float alpha)
{
	int startY = (int)floor(r_start._y);
	int endY = (int)ceil(r_end._y);
	Vector2 direction = (r_end - r_start);
	float xMovement = direction.NormalizedY()._x;

	//The vector is going left or right, we must determine which horizontal segments we check, we'll only check those that are going to cross the vector
	int startX = (int)ceil(r_start._x);
	if (r_end._x > r_start._x)
	{
		startX = (int)floor(r_start._x);
	}

	float luminancesCache[WIDTH][HEIGHT]={0};
	
	for(int y = startY;y < endY;y++) {
		//We find on which y the collision with the next vertical line will happen
		float nextX = (float)startX + (float)(y - startY) * xMovement;

		//We apply the principles of Xiaolin Wu's algorithm to calculate the luminance of the two pixels to place
		//https://www.geeksforgeeks.org/anti-aliased-line-xiaolin-wus-algorithm/
		float decimalPartOfX=nextX-floor(nextX);

		int inextX=(int)floor(nextX);
		if(inextX<0) continue;
		if (inextX >= WIDTH - 1) continue;
		if (y >= HEIGHT - 1) continue;
		if (y < 0) continue;
		luminancesCache[inextX][y]+=1-decimalPartOfX;
		luminancesCache[inextX+1][y]+=decimalPartOfX;
		
		ColorPixel(inextX, y, color,alpha*luminancesCache[inextX][y]);
		ColorPixel(inextX+1, y, color,alpha*luminancesCache[inextX+1][y]);
	}
}

void Drawable::DrawRectangle(Vector2 startPoint, Vector2 endPoint, const int color, const float alpha, bool drawBorders,bool drawAsBackgroundPixels)
{
	if (startPoint._x > endPoint._x) {
		float cache = startPoint._x;
		startPoint._x = endPoint._x;
		endPoint._x = cache;
	}

	if (startPoint._y > endPoint._y) {
		float cache = startPoint._y;
		startPoint._y = endPoint._y;
		endPoint._y = cache;
	}

	if (!drawBorders) {
		++startPoint._x;
		++startPoint._y;
		--endPoint._x;
		--endPoint._y;
	}

	if(startPoint._x<0) startPoint._x=0;
	if(startPoint._y<0) startPoint._y=0;
	if(endPoint._x>=WIDTH) endPoint._x=WIDTH-1;
	if(endPoint._y>=HEIGHT) endPoint._y=HEIGHT-1;

	//We can't call ColorPixel because it'd break the stack for huge rectangles
	Console& r_console = Console::GetInstance();
	int charToUseIndex = (int)std::floor(alpha * (SORTED_BY_LUMINANCE_STRING.length() - 1));
	WCHAR charToUse = drawAsBackgroundPixels ? ' ' : SORTED_BY_LUMINANCE_STRING.at(charToUseIndex);

	auto charInfo = (WORD)color << (drawAsBackgroundPixels ? 4 : 0);

	for (int x = ceil(startPoint._x); x <= floor(endPoint._x); ++x) 
	{
		for (int y = ceil(startPoint._y); y <= floor(endPoint._y); ++y)
		{
			r_console._virtual_buffer[x][y].charToUse = charToUse;
			if (!drawAsBackgroundPixels) {
				r_console._virtual_buffer[x][y].color = (WORD)color;
				continue;
			}
			r_console._virtual_buffer[x][y].backgroundColor = (WORD)color;
		}
	}
}

const std::string Drawable::SORTED_BY_LUMINANCE_STRING=".,:;i1tfcLCXO0W@";

void Drawable::ColorPixel(const int x,const int y,const int color,const float alpha, bool backgroundPixel) {
	if(x < 0 || y < 0) return;
	Console& r_console = Console::GetInstance();

	int charToUseIndex=(int)std::floor(alpha*(SORTED_BY_LUMINANCE_STRING.length()-1));
	WCHAR charToUse= backgroundPixel ? ' ' : SORTED_BY_LUMINANCE_STRING.at(charToUseIndex);
	
	r_console._virtual_buffer[x][y].charToUse = charToUse;
	if (!backgroundPixel) {
		r_console._virtual_buffer[x][y].color = (WORD)color;
		return;
	}
	r_console._virtual_buffer[x][y].backgroundColor = (WORD)color;
}

}

