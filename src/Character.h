#pragma once
#include "Drawable.h"

class Character : public Drawable {
public:
	void draw(Console& console);
};