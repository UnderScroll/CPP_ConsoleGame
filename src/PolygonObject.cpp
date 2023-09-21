#include "PolygonObject.h"

#include <cmath>

#include "Drawable.h"

PolygonObject PolygonObject::CreateRectangle(float x, float y, float width, float height, int color)
{
    std::vector<Vector2> points;
    points.push_back(Vector2(-0.5f * width, -0.5f * height));
    points.push_back(Vector2(0.5f * width, -0.5f * height));
    points.push_back(Vector2(0.5f * width, 0.5f * height));
    points.push_back(Vector2(-0.5f * width, 0.5f * height));
    PolygonObject rectangle = PolygonObject(points, color);
    rectangle.MoveTo(Vector2(x, y));
    return rectangle;
}

PolygonObject PolygonObject::CreateLine(float x, float y, float length, int color)
{
    std::vector<Vector2> points;
    points.push_back(Vector2(-0.5f*length, 0));
    points.push_back(Vector2(0.5f*length, 0));
    PolygonObject line = PolygonObject(points, color,false);
    line.MoveTo(Vector2(x, y));
    return line;
}

PolygonObject PolygonObject::CreateLine(float x1, float y1, float x2, float y2, int color)
{
    Vector2 startPoint(x1,y1);
    Vector2 endPoint(x2,y2);
    Vector2 middlePoint=startPoint+0.5*(endPoint-startPoint);
    float magnitude=(endPoint-startPoint).Magnitude();

    float angle=atan2(y2-y1,x2-x1)+PI_F/2; //The angle that the line is facing
    PolygonObject line=CreateLine(middlePoint._x,middlePoint._y,magnitude,color);
    line.RotateToRadians(angle);
    return line;
}

void PolygonObject::Draw()
{
    for (int i = 0; i < _rotated_points.size() - ((_isClosed) ? 0 : 1); ++i)
    {
        Vector2 currentPoint = GetPosition() + _rotated_points[i];
        Vector2 nextPoint = GetPosition() + _rotated_points[(i < _rotated_points.size() - 1) ? i + 1 : 0];

        Drawable::ProcessLine(currentPoint, nextPoint, _color);
    }
}

void PolygonObject::RotateToRadians(float targetAngle)
{
    GameObject::RotateToRadians(targetAngle);
    _rotated_points.clear();
    for (Vector2 point : _points)
    {
        _rotated_points.push_back(point.RotateByRadians(GetRotationInRadians()));
    }
}
