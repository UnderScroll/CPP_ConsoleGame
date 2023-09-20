#pragma once
#include "Vector2.h"

class Console;

class Drawable {
public:
	virtual void Draw()=0;
	void ProcessLine(const Vector2& r_start, const Vector2& r_end, const int color);

	static void ColorPixel(const int x,const int y, const int color, const float proportion=1, const float alpha=1);
private:
	void ProcessHorizontalLine( const Vector2& r_start, const Vector2& r_end, const int color);
	void ProcessVerticalLine(const Vector2& r_start, const Vector2& r_end, const int color);
};