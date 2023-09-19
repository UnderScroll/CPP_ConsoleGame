#pragma once

class Console;

class Drawable {
public:
	virtual void Draw(Console& console)=0;
	void ProcessLine(Console& console, Vector2 start, Vector2 end);
};