#include "GameObject.h"

#include "Application.h"

void GameObject::Update()
{
	UpdateGameObjectPointersList(_children);
}

void GameObject::UpdateGameObjectPointersList(std::vector<std::shared_ptr<GameObject>>& r_game_objects)
{
	for (auto itr = r_game_objects.begin(); itr != r_game_objects.end(); ++itr)
	{
		if ((*itr)->_destroyed)
		{
			r_game_objects.erase(itr);
			return;
		}

		(*itr)->Update();
	}
}

void GameObject::Draw()
{
	for (auto child : _children)
	{
		child->Draw();
	}
}

Vector2 GameObject::GetWorldPosition() const
{
	if (_parent == nullptr) return GetLocalPosition();
	auto rotatedLocalPosition= GetLocalPosition().RotateByRadians(_parent->GetWorldRotationInRadians());
	return rotatedLocalPosition + _parent->GetWorldPosition();
}

float GameObject::GetWorldRotationInRadians()
{
	if (_parent == nullptr) return GetLocalRotationInRadians();
	return _parent->GetWorldRotationInRadians() + GetLocalRotationInRadians();
}

float GameObject::GetWorldRotationInDegrees()
{
	return GetWorldRotationInRadians() * RAD_TO_DEG;
}

void GameObject::RotateToRadians(float targetAngle)
{
	//TO DO : Utiliser GetWorldPosition
	_localRotation = targetAngle;
	for (auto child : _children) {
		//Recalculate variables suposed to be recalculated when the piece is rotated
		child->RotateByDegrees(0);
	}
}

inline void GameObject::DetachFromParent()
{
	if (_parent == nullptr) return;
	for (auto itr = _parent->_children.begin(); itr != _parent->_children.end(); ++itr)
	{
		_parent->_children.erase(itr);
		break;
	}

	_parent = nullptr;
}

void GameObject::AddChild(std::shared_ptr<GameObject> newChildPtr)
{
	if (newChildPtr->_parent != nullptr)
	{
		throw std::runtime_error("Tried to add a child that already had a parent to a game object");
	}
	newChildPtr->_parent = shared_from_this();
	_children.push_back(newChildPtr);
	Application::RemoveGameObject(newChildPtr);
}
