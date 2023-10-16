#pragma once
#include <vector>

#include "Polygon.h"
#include "UIRect.h"
#include "HorizontalLayoutGroup.h"
#include "Laser.h"

namespace core {
	class Level
	{
	public:
		virtual void LoadLevel();
		static void ClearCurrentLevel();

		std::vector<Polygon> _movableElements;
		std::vector<Polygon> _staticNonReflectivesElements;
		std::vector<Polygon> _staticReflectivesElements;

		bool _bottomHudOn = true;
		bool _topHudOn = true;
		
		std::shared_ptr<HorizontalLayoutGroup> _bottomHud;
		std::shared_ptr<HorizontalLayoutGroup> _topHud;

		std::string _levelName="Level";
	};
}


