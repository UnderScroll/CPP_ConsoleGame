#pragma once
#include "../Level.h"

namespace core::levels {

class Level5 :
    public Level
{
public:
	Level5() {
		_levelName = "Level 5";
	}

	void LoadLevel();
};

}

