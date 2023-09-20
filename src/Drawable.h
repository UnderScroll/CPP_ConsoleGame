#pragma once
#include "Vector2.h"

class Console;

class Drawable {
public:
	virtual void Draw(Console& console)=0;
	void ProcessLine(Console& console, Vector2 start, Vector2 end);
private:
	void ProcessHorizontalLine(Console& console, Vector2 start, Vector2 end);
	void ProcessVerticalLine(Console& console, Vector2 start, Vector2 end);
};