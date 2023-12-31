#pragma once
#include <vector>

#include "Polygon.h"
#include "UIRect.h"
#include "HorizontalLayoutGroup.h"
#include "Laser.h"
#include "Sensor.h"

namespace core {
	/*
	Main class for level loading
	*/
	class Level
	{
	public:
		virtual void LoadLevel();
		static void ClearCurrentLevel();

		//The different kind of objects in a level
		std::vector<Polygon> _movableElements;
		std::vector<Polygon> _rotatableElements;
		std::vector<Polygon> _staticNonReflectivesElements;
		std::vector<Polygon> _staticReflectivesElements;
		Vector2 _sensorPos = Vector2();

		std::vector<Laser> _lasers;

		bool _bottomHudOn = true;
		bool _topHudOn = true;
		
		std::shared_ptr<HorizontalLayoutGroup> _bottomHud;
		std::shared_ptr<HorizontalLayoutGroup> _topHud;

		std::string _levelName="Level";
	};
}


