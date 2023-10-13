#pragma once
#include <vector>

#include "GameObject.h"
#include "Vector2.h"

class PolygonObject :
    public GameObject
{
public:
    std::vector<Vector2> _points; //Coordinates are relatives to the position of the GameObject
    int _color;
    float _alpha;
    bool _isClosed;

    static std::shared_ptr<PolygonObject> CreateRectangle(float x, float y,float width, float height,int color=0x0007);
    static std::shared_ptr<PolygonObject> CreateLine(float x, float y,float length,int color=0x0007);
    static std::shared_ptr<PolygonObject> CreateLine(float x1, float y1,float x2,float y2,int color=0x0007);
    static std::shared_ptr<PolygonObject> CreatePolygon();
    static std::shared_ptr<PolygonObject> CreatePolygon(std::vector<Vector2> points, bool isClosed=true,int color=0x0007, float alpha=1.0f);
    static std::shared_ptr<PolygonObject> CreatePolygon(const PolygonObject polygon_object);
    
    // H�rit� via GameObject
    virtual void Draw() override;
    virtual void RotateToRadians(float targetAngle) override;
    virtual void Update() override {}
protected:
    PolygonObject(std::vector<Vector2> points, bool isClosed,int color, float alpha):_points(points),_color(color),
        _alpha(alpha), _isClosed(isClosed)
    {
        _rotated_points = _points;
    }
    
    static PolygonObject RectangleConstructor(float x, float y, float width, float height, int color);
    static PolygonObject LineConstructor(float x, float y, float length, int color);
    static PolygonObject LineConstructor(float x1, float y1, float x2, float y2, int color);

    std::vector<Vector2> _rotated_points;
};

