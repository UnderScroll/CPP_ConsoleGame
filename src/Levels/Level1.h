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
			_movableElements = {
				Rectangle(50,80),
				Polygon({Vector2(-10, -10), Vector2(10, -10),Vector2(0, 10)},true),
			};

			_staticNonReflectivesElements = {
				//(std::vector<Vector2> points, bool isClosed, Color color = WHITE, float alpha = 1, Vector2 localPosition = Vector2(0, 0), Vector2 localScale = Vector2(1, 1), float localRotation = 0)
				Polygon({Vector2(0,-50), Vector2(0,50)},false,Drawable::RED,1,Vector2(40,80),Vector2(1,1),3.14/2),
				Polygon({Vector2(-50,0), Vector2(50,0)},false,Drawable::RED,1,Vector2(40,WIDTH-80),Vector2(1,1),3.14 / 2),
			};
		}
	};
}


