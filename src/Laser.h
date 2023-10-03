#pragma once
#include "GameObject.h"
#include "PolygonObject.h"

#include <windows.h>

class Laser : public GameObject
{
public:
	Laser();
	Laser(const float size);


	const float size;
	const int color = FOREGROUND_BLUE;

	void Draw();
	void Update();
	void ComputeLaserLine();
private:

	std::shared_ptr<PolygonObject> laserBase;
	std::shared_ptr<PolygonObject> laserLine;
};

