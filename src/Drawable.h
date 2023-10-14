#pragma once
#include <string>

#include "Vector2.h"

namespace core {

class Drawable {
public:
	virtual void Draw()=0;
	static void DrawLine(const Vector2& r_start, const Vector2& r_end, const int color, const float alpha=1);
	static void DrawRectangle(Vector2 startPoint, Vector2 endPoint, const int color, const float alpha, bool drawBorders = true, bool drawAsBackgroundPixels=false);
	
	static void ColorPixel(const int x,const int y, const int color, const float alpha=1, bool backgroundPixel=false);

	enum Color {
		WHITE = 0x0007,
		RED = 0x0004,
		BLUE = 0x0001,
		GREEN = 0x0002,
		YELLOW = 0x0006,
		CYAN = 0x0003,
		MAGENTA = 0x0005,
		BLACK = 0x0000
	};

	static const std::string SORTED_BY_LUMINANCE_STRING;

	enum Layer {
		BACKGROUND,
		WORLD,
		UI
	};

	Layer _layer = WORLD;

private:
	static void ProcessHorizontalLine( const Vector2& r_start, const Vector2& r_end, const int color, const float alpha);
	static void ProcessVerticalLine(const Vector2& r_start, const Vector2& r_end, const int color, const float alpha);
};

}

