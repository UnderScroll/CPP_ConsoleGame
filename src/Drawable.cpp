#pragma once
#include "Drawable.h"

#include <math.h>
#include <vector>

#include "Console.h"
#include <map>

#define PIXEL_COORDS std::pair<int, int>

namespace core {

	const Drawable::Layer Drawable::LAYERS[] = { BACKGROUND,WORLD,UI };

#pragma region Drawing Lines
	//https://en.wikipedia.org/wiki/Xiaolin_Wu%27s_line_algorithm Xialoin Wu's anti-aliasing line algorithm

	// integer part of x
	int ipart(float x) {
		return floor(x);
	}


	int round(float x) {
		return ipart(x + 0.5);
	}

	// fractional part of x
	float fpart(float x) {
		return x - ipart(x);
	}


	float rfpart(float x) {
		return 1 - fpart(x);
	}

	void setPixelBrightness(int x, int y, float brightness,std::map<PIXEL_COORDS, float> &r_pixelsBrightesses) {
		float oldBrightness = 0;
		if (r_pixelsBrightesses.contains({x,y })){
			oldBrightness = r_pixelsBrightesses[{ x,y }];
		}

		float newBrightness = std::max<float>(oldBrightness, brightness);
		r_pixelsBrightesses[{x,y}] = newBrightness;
	}

	void Drawable::DrawLine(const Vector2& r_start, const Vector2& r_end, const int color, const float alpha)
	{
		float x0 = r_start._x;
		float y0 = r_start._y;
		float x1 = r_end._x;
		float y1 = r_end._y;

		std::map<PIXEL_COORDS,float> pixelsBrightnesses= std::map<PIXEL_COORDS, float>();

		boolean steep = abs(y1 - y0) > abs(x1 - x0);

		if (steep)
		{
			std::swap(x0, y0);
			std::swap(x1, y1);
		}

		if (x0 > x1)
		{
			std::swap(x0, x1);
			std::swap(y0, y1);
		}

		float dx = x1 - x0;
		float dy = y1 - y0;

		float gradient = 1.0f;
		if (dx != 0.0) {
			gradient = dy / dx;
		}

		// handle first endpoint
		float xend = round(x0);
		float yend = y0 + gradient * (xend - x0);
		float xgap = rfpart(x0 + 0.5);
		int xpxl1 = xend; // this will be used in the main loop
		float ypxl1 = ipart(yend);
		if (steep) {
			setPixelBrightness(ypxl1, xpxl1, rfpart(yend) * xgap, pixelsBrightnesses);
			setPixelBrightness(ypxl1 + 1, xpxl1, fpart(yend) * xgap, pixelsBrightnesses);
		}
		else
		{
			setPixelBrightness(xpxl1, ypxl1, rfpart(yend) * xgap, pixelsBrightnesses);
			setPixelBrightness(xpxl1, ypxl1 + 1, fpart(yend) * xgap, pixelsBrightnesses);
		}
		float intery = yend + gradient; // first y-intersection for the main loop

		// handle second endpoint
		xend = round(x1);
		yend = y1 + gradient * (xend - x1);
		xgap = fpart(x1 + 0.5);
		int xpxl2 = xend; //this will be used in the main loop
		int ypxl2 = ipart(yend);
		if (steep) {
			setPixelBrightness(ypxl2, xpxl2, rfpart(yend) * xgap,pixelsBrightnesses);
			setPixelBrightness(ypxl2 + 1, xpxl2, fpart(yend) * xgap, pixelsBrightnesses);
		}
		else {
			setPixelBrightness(xpxl2, ypxl2, rfpart(yend) * xgap, pixelsBrightnesses);
			setPixelBrightness(xpxl2, ypxl2 + 1, fpart(yend) * xgap, pixelsBrightnesses);
		}

		// main loop
		if (steep) {
			for (int x = xpxl1 + 1; x < xpxl2; x++) {
				setPixelBrightness(ipart(intery), x, rfpart(intery), pixelsBrightnesses);
				setPixelBrightness(ipart(intery) + 1, x, fpart(intery), pixelsBrightnesses);
				intery += gradient;
			}
		}
		else {
			for (int x = xpxl1 + 1; x < xpxl2; x++) {
				setPixelBrightness(x, ipart(intery), rfpart(intery), pixelsBrightnesses);
				setPixelBrightness(x, ipart(intery) + 1, fpart(intery), pixelsBrightnesses);
				intery += gradient;
			}
		}

		for (auto pixelBrightness : pixelsBrightnesses) {

			ColorPixel(pixelBrightness.first.first, pixelBrightness.first.second, color, pixelBrightness.second);
		}
	}
#pragma endregion

	void Drawable::DrawRectangle(Vector2 startPoint, Vector2 endPoint, const int color, const float alpha, bool drawBorders, bool drawAsBackgroundPixels)
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

		if (startPoint._x < 0) startPoint._x = 0;
		if (startPoint._y < 0) startPoint._y = 0;
		if (endPoint._x >= WIDTH) endPoint._x = WIDTH - 1;
		if (endPoint._y >= HEIGHT) endPoint._y = HEIGHT - 1;

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

	const std::string Drawable::SORTED_BY_LUMINANCE_STRING = ".,:;i1tfcLCXO0W@";

	void Drawable::ColorPixel(const int x, const int y, const int color, const float alpha, bool backgroundPixel) {
		if (x < 0 || y < 0) return;
		if (x >= WIDTH || y >= HEIGHT) return;

		Console& r_console = Console::GetInstance();

		int charToUseIndex = (int)std::floor(alpha * (SORTED_BY_LUMINANCE_STRING.length() - 1));
		WCHAR charToUse = backgroundPixel ? ' ' : SORTED_BY_LUMINANCE_STRING.at(charToUseIndex);

		r_console._virtual_buffer[x][y].charToUse = charToUse;
		if (!backgroundPixel) {
			r_console._virtual_buffer[x][y].color = (WORD)color;
			return;
		}
		r_console._virtual_buffer[x][y].backgroundColor = (WORD)color;
	}

}

