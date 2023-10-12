#include "GameObject.h"

#include "Application.h"

namespace core {

std::vector<std::shared_ptr<GameObject >> GameObject::_rootGameObjects = std::vector<std::shared_ptr<GameObject>>();

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
	if (_parent.expired()) return GetLocalPosition();
	auto parent = _parent.lock();
	auto rotatedLocalPosition= GetLocalPosition().RotateByRadians(parent->GetWorldRotationInRadians());
	return rotatedLocalPosition + parent->GetWorldPosition();
}

float GameObject::GetWorldRotationInRadians()
{
	if (_parent.expired()) return GetLocalRotationInRadians();
	auto parent = _parent.lock();
	return parent->GetWorldRotationInRadians() + GetLocalRotationInRadians();
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
	if (_parent.expired()) return;
	auto parent = _parent.lock();
	for (auto itr = parent->_children.begin(); itr != parent->_children.end(); ++itr)
	{
		parent->_children.erase(itr);
		break;
	}

	_localPosition = GetWorldPosition();
	_parent.reset();
}

void GameObject::AddChild(std::shared_ptr<GameObject> newChildPtr)
{
	if (!newChildPtr->_parent.expired())
	{
		throw std::runtime_error("Tried to add a child that already had a parent to a game object. If you want to change the parent of a game object your must call DetachFromParent first.");
	}
	//Change the local position of the new child so that it can stay at the same position in the world even though it now has a parent.
	newChildPtr->SetLocalPosition(newChildPtr->GetWorldPosition() - GetWorldPosition());

	newChildPtr->_parent = shared_from_this();

	_children.push_back(newChildPtr);
}

template<typename T>
std::shared_ptr<T> GameObject::AddChild(T gameObject)
{
	auto ptr= std::make_shared<T>(gameObject);
	AddChild(ptr);
	return ptr;
}

template <typename T>
std::shared_ptr<T> GameObject::AddGameObjectToRoot(T gameObject)
{
	auto newObject = std::make_shared<T>(gameObject);
	_rootGameObjects.push_back(newObject);
	return newObject;
}

}

