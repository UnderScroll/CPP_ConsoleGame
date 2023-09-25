#pragma once
#include <memory>
#include <numbers>

#include "Drawable.h"
#include "Collider.h"

class GameObject :
    public Drawable,
    public Collider 
{
    // H�rit� via Drawable
public:
    bool _destroyed=false; //When true, the application will delete it from its vectors

    //All children of GameObject must implement a static factory method ! Sadly, there's no way to define a static virtual function :(
    //Don't forget to make all the constructor private or protected
    virtual void Update(){}
    
    virtual void Draw()=0;

    virtual void Destroy()
    {
        _destroyed=true;
    }

    //The function relative to position and rotation are virtual so that children can redefine them. This is useful for polygons that needs special code to run to rotate correctly
    virtual Vector2 GetPosition() const
    {
        return _position;
    }
    virtual void MoveBy(Vector2 deltaPosition)
    {
        _position+=deltaPosition;
    }

    virtual void MoveTo(Vector2 targetPosition)
    {
        _position=targetPosition;
    }

    virtual float GetRotationInRadians()
    {
        return _rotation;
    }

    virtual  float GetRotationInDegrees()
    {
        return GetRotationInRadians()*RAD_TO_DEG;
    }

    virtual  void RotateByRadians(float deltaAngle)
    {
        RotateToRadians(_rotation+deltaAngle);
    }

    virtual void RotateByDegrees(float deltaAngle)
    {
        RotateByRadians(deltaAngle*DEG_TO_RAD);
    }

    virtual  void RotateToRadians(float targetAngle)
    {
        _rotation=targetAngle;
    }

    virtual void RotateToDegrees(float targetAngle)
    {
        _rotation=DEG_TO_RAD*targetAngle;
    }
protected:
    Vector2 _position = { 0, 0 };
    //In radians
    float _rotation = 0;
    GameObject() {}
};

