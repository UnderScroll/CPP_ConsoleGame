#pragma once
#include "Drawable.h"
#include "Vector2.h"

class Character : public Drawable {
public:
	void Draw();

	Vector2 _pos;
};