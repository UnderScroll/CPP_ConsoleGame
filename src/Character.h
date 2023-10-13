#pragma once
#include "Drawable.h"
#include "Vector2.h"

namespace core {

class Character : public Drawable {
public:
	void Draw();

	Vector2 _pos;
};

}

