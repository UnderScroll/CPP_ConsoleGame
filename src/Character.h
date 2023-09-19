#pragma once
#include "Drawable.h"
#include "Vec2.h"

class Character : public Drawable {
public:
	void Draw(Console& console);

	Vec2 pos;
};