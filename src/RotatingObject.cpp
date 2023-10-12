#include "RotatingObject.h"

#include "Application.h"

namespace core {

void RotatingObject::Update()
{
    GameObject::Update();
    RotateByDegrees(_angularVelocity);
}

}

