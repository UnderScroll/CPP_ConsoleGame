#include "RotatingObject.h"

#include "Application.h"


std::shared_ptr<RotatingObject> RotatingObject::CreateRotatingObject(float x, float y, float angularVelocity,
                                                                     std::shared_ptr<GameObject> r_child)
{
    auto newObject=std::make_shared<RotatingObject>(RotatingObject(angularVelocity));
    newObject->MoveTo(Vector2(x,y));
    newObject->AddChild(r_child);
    Application::AddGameObject(newObject);
    return newObject;
}

void RotatingObject::Update()
{
    GameObject::Update();
    RotateByDegrees(_angularVelocity);
}
