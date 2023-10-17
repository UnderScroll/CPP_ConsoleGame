#pragma once
#include "../Level.h"
#include "../Rectangle.h"
#include "../Console.h"

namespace core::levels {

class Level1 :
	public Level
{
public:
	Level1() {
		_levelName = "Level 1";
	}

	void LoadLevel();
};

}


