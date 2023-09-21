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
    float _alpha;
    bool _isClosed;

    PolygonObject()
    {
        _color=0x0007;
        _isClosed=true;
    }

    PolygonObject(std::vector<Vector2> points,int color, bool isClosed=true):_points(points),_color(color),_isClosed(isClosed) {
    }

    static PolygonObject CreateRectangle(float x, float y,float width, float height,int color=0x0007);
    static PolygonObject CreateLine(float x, float y,float length,int color=0x0007);
    static PolygonObject CreateLine(float x1, float y1,float x2,float y2,int color=0x0007);
    
    // H�rit� via GameObject
    virtual void Draw() override;
    virtual void RotateToRadians(float targetAngle) override;
private:
    std::vector<Vector2> _rotated_points;
};

