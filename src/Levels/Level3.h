#pragma once
#include "../Level.h"

namespace core::levels {

class Level3 :
    public Level
{
public:
	Level3() {
		_levelName = "Level 3";
	}

	void LoadLevel();
};

}



