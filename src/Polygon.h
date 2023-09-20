#pragma once
#include "GameObject.h"
#include <vector>
#include "Vector2.h"

class Polygon :
    public GameObject
{
public:
    std::vector<Vector2> _points; //Exprimée relativement au centre de gravité du polygon
    int _color;

    Polygon(std::vector<Vector2> points,int color):_points(points),_color(color) {

    }

    // Hérité via GameObject
    virtual void Draw() override;

};

