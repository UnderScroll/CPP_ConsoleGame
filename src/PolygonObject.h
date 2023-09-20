#pragma once
#include <vector>

#include "GameObject.h"
#include "Vector2.h"

class PolygonObject :
    public GameObject
{
public:
    std::vector<Vector2> _points; //Exprim�e relativement au centre de gravit� du polygon
    int _color;

    PolygonObject(){}

    PolygonObject(std::vector<Vector2> points,int color):_points(points),_color(color) {

    }

    // H�rit� via GameObject
    virtual void Draw() override;

};

