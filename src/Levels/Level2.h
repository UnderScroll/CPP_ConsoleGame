#pragma once
#include "../Level.h"

namespace core::levels {

class Level2 :
    public Level
{
public:
	Level2() {
		_levelName = "Level 2";
	}

	void LoadLevel();
};

}