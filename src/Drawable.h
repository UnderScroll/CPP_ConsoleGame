#pragma once
#include <string>

#include "Vector2.h"

class Console;

class Drawable {
public:
	virtual void Draw()=0;
	static void ProcessLine(const Vector2& r_start, const Vector2& r_end, const int color, const float alpha=1);
	
	static void ColorPixel(const int x,const int y, const int color, const float alpha=1);

	static const std::string SORTED_BY_LUMINANCE_STRING;
private:
	static void ProcessHorizontalLine( const Vector2& r_start, const Vector2& r_end, const int color, const float alpha);
	static void ProcessVerticalLine(const Vector2& r_start, const Vector2& r_end, const int color, const float alpha);
};