#pragma once
#include "../Level.h"
#include "../Rectangle.h"
#include "../Console.h"

namespace core::levels {
	class LevelEndMenu :
		public Level
	{
	public:
		LevelEndMenu() {
			_topHudOn = false;
			_bottomHudOn = false;
		}

		virtual void LoadLevel() override;
	};
}


