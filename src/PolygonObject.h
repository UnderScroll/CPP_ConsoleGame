#pragma once
#include <vector>

#include "GameObject.h"
#include "Vector2.h"

class PolygonObject :
    public GameObject
{
public:
    std::vector<Vector2> _points; //Exprimée relativement au centre de gravité du polygon
    int _color;

    PolygonObject(){}

    PolygonObject(std::vector<Vector2> points,int color):_points(points),_color(color) {

    }

    // Hérité via GameObject
    virtual void Draw() override;

};

