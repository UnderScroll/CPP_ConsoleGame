#pragma once
#include "GameObject.h"
#include "Polygon.h"

namespace core {

class Laser : 
	public GameObject
{
public:
	Laser();
	Laser(const float size);

	const float size;
	const int color = 1;

	void Draw() override;
	void Update();
	void ComputeLaserLine();
private:
	Polygon laseBase;
	Polygon laseLine;
};

}
