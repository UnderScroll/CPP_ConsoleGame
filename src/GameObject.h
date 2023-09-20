#pragma once
#include "Drawable.h"
#include "Collider.h"

class GameObject :
    public Drawable,
    public Collider 
{
    // H�rit� via Drawable
public:
    virtual void Draw()=0;
    Vector2 _position = { 0, 0 };
    float _rotation = 0;
};

