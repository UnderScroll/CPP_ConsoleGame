#include "GameObject.h"

#include "Application.h"

void GameObject::Update()
{
    UpdateGameObjectPointersList(_children);
}

void GameObject::UpdateGameObjectPointersList(std::vector<std::shared_ptr<GameObject>> &r_game_objects)
{
    for (auto itr = r_game_objects.begin(); itr != r_game_objects.end(); ++itr)
    {
        if ((*itr)->_destroyed)
        {
            r_game_objects.erase(itr);
            return;
        }

        if((*itr)->_detached)
        {
            Application::AddGameObject(*itr);
            r_game_objects.erase(itr);
        }
        
        (*itr)->Update();
    }
}

void GameObject::Draw()
{
    for(auto child : _children)
    {
        child->Draw();
    }
}

//TO DO : recoder parce que ça doit bouger l'enfant
void GameObject::RotateToRadians(float targetAngle)
{
    float deltaRotation=targetAngle-_rotation;
    for (auto child : _children)
    {
        float localRotation=child->_rotation-this->_rotation;
        //child->RotateByRadians(deltaRotation);
        auto debug = (child->GetPosition() - GetPosition());
        auto debug2 = child->GetPosition();
        auto debug3 = GetPosition();
        auto debug4 = 8;
        child->MoveTo(GetPosition() + debug.RotateByRadians(deltaRotation));
    }
    _rotation = targetAngle;
}

void GameObject::AddChild(std::shared_ptr<GameObject> newChildPtr, bool convertCoordinatesToLocalCoordinates)
{
    
        _children.push_back(newChildPtr);
        if(!convertCoordinatesToLocalCoordinates) return;
        newChildPtr->MoveTo(_position+newChildPtr->GetPosition());
    Application::RemoveGameObject(newChildPtr);
}
