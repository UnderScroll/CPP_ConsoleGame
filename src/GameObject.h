#pragma once
#include <memory>
#include <numbers>
#include <vector>

#include "Drawable.h"
#include "Collider.h"

class GameObject :
    public Drawable,
    public Collider 
{
    // inherited by via Drawable
public:
    bool _destroyed=false; //When true, the application will delete it from its vectors
    bool _detached=false; //When true, the parent game object will remove it from their child and add it to the main game objects list

    //All children of GameObject must implement a static factory method ! Sadly, there's no way to define a static virtual function :(
    //Don't forget to make all the constructor private or protected
    virtual void Update();
    
    void static UpdateGameObjectPointersList(std::vector<std::shared_ptr<GameObject>> &r_game_objects);
    
    virtual void Draw();

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
        MoveTo(_position+deltaPosition);
    }

    virtual void MoveTo(Vector2 targetPosition)
    {
        _position = targetPosition;
        for (auto child : _children)
        {
            Vector2 localPosition=child->_position-this->_position;
            child->MoveTo(targetPosition+localPosition);
        }
    }

    virtual float GetRotationInRadians()
    {
        return _rotation;
    }

    virtual  float GetRotationInDegrees()
    {
        return GetRotationInRadians() * RAD_TO_DEG;
    }

    void RotateByRadians(float deltaAngle)
    {
        RotateToRadians(_rotation + deltaAngle);
    }

    void RotateByDegrees(float deltaAngle)
    {
        RotateByRadians(deltaAngle * DEG_TO_RAD);
    }

    virtual void RotateToRadians(float targetAngle)
    {
        for (auto child : _children)
        {
            float localRotation=child->_rotation-this->_rotation;
            child->RotateToRadians(targetAngle+localRotation);
        }
        _rotation = targetAngle;
    }

    void RotateToDegrees(float targetAngle)
    {
        RotateToRadians(DEG_TO_RAD * targetAngle);
    }

    void DetachFromParent()
    {
        _detached=true;
    }

    /**
     * \brief 
     * \param newChildPtr 
     * \param convertCoordinatesToLocalCoordinates If true, the current coordinates of the object will be interpreted as local coordinates. If the GameObject is at (0,0), he will be moved to be at the center of its parent
     */
    void AddChild(std::shared_ptr<GameObject> newChildPtr, bool convertCoordinatesToLocalCoordinates=true);

    std::vector<std::shared_ptr<GameObject>> _children;
protected:
    Vector2 _position = { 0, 0 };
    //In radians
    float _rotation = 0;
    GameObject() {}
};

