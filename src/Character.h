#pragma once
#include "Drawable.h"
#include "Vec2.h"

class Character : public Drawable {
public:
	void Draw();

	Vec2 pos;
};