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
		BLACK = 0x0000,
		GRAY = 0x0008,
		LIGHTER_WHITE = 0x000F,
		LIGHT_BLUE=0x0009,
		LIGHT_GREEN=0x000A,
		LIGHT_CYAN=0x000B,	
	};

	static const std::string SORTED_BY_LUMINANCE_STRING;

	enum Layer {
		BACKGROUND,
		WORLD,
		UI
	};

	Layer _layer = WORLD;
	const static Layer LAYERS[];
	const static int LAYERS_COUNT=3;
};

}

