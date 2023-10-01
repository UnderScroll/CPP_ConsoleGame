#pragma once
#include <numbers>

#include "Drawable.h"
#include "Collider.h"

class GameObject :
    public Drawable,
    public Collider 
{
    // inherited by via Drawable
public:
    virtual void Draw() = 0;

    //The function relative to position and rotation are virtual so that children can redefine them. This is useful for polygons that needs special code to run to rotate correctly
    virtual Vector2 GetPosition() const
    {
        return _position;
    }
    virtual void MoveBy(Vector2 deltaPosition)
    {
        _position += deltaPosition;
    }

    virtual void MoveTo(Vector2 targetPosition)
    {
        _position = targetPosition;
    }

    virtual float GetRotationInRadians()
    {
        return _rotation;
    }

    virtual  float GetRotationInDegrees()
    {
        return GetRotationInRadians() * RAD_TO_DEG;
    }

    virtual  void RotateByRadians(float deltaAngle)
    {
        RotateToRadians(_rotation + deltaAngle);
    }

    virtual void RotateByDegrees(float deltaAngle)
    {
        RotateByRadians(deltaAngle * DEG_TO_RAD);
    }

    virtual  void RotateToRadians(float targetAngle)
    {
        _rotation = targetAngle;
    }

    virtual void RotateToDegrees(float targetAngle)
    {
        _rotation= DEG_TO_RAD * targetAngle;
    }
protected:
    Vector2 _position = { 0, 0 };
    //In radians
    float _rotation = 0;
};

