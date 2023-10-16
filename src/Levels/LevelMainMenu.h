#pragma once
#include "../Level.h"
#include "../Rectangle.h"
#include "../Console.h"

namespace core::levels {
	class LevelMainMenu :
		public Level
	{
	public:
		LevelMainMenu() {
			_topHudOn = false;
			_bottomHudOn = false;
		}

		virtual void LoadLevel() override;
	};
}


