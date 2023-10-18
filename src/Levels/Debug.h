#pragma once
#include "../Level.h"

namespace core::levels {

class Debug :
	public Level
{
public:
	Debug() {
		_levelName = "Debug !";
	}

	void LoadLevel();
};

}

