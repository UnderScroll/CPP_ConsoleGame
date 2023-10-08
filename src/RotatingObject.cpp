#include "RotatingObject.h"

#include "Application.h"

namespace core {

std::shared_ptr<RotatingObject> RotatingObject::CreateRotatingObject(float x, float y, float angularVelocity,
                                                                     std::shared_ptr<GameObject> r_child)
{
    auto newObject=std::make_shared<RotatingObject>(RotatingObject(angularVelocity));
    newObject->SetLocalPosition(Vector2(x,y));
    newObject->AddChild(r_child);
    return newObject;
}

void RotatingObject::Update()
{
    GameObject::Update();
    RotateByDegrees(_angularVelocity);
}


}

