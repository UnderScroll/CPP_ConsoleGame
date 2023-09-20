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
    bool _isClosed;

    PolygonObject(){}

    PolygonObject(std::vector<Vector2> points,int color, bool isClosed=true):_points(points),_color(color),_isClosed(isClosed) {
    }
    
    // H�rit� via GameObject
    virtual void Draw() override;

};

