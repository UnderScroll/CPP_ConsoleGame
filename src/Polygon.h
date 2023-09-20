#pragma once
#include "GameObject.h"
#include <vector>
#include "Vector2.h"

class Polygon :
    public GameObject
{
public:
    std::vector<Vector2> _points; //Exprim�e relativement au centre de gravit� du polygon
    int _color;

    Polygon(std::vector<Vector2> points,int color):_points(points),_color(color) {

    }

    // H�rit� via GameObject
    virtual void Draw() override;

};

