#pragma once
#include "../Level.h"

namespace core::levels {

class Level4 :
    public Level
{
public:
    Level4() {
		_levelName = "Level 4";
	}

	void LoadLevel();
};

}



