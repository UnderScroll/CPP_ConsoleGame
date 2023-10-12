#pragma once
#include "GameObject.h"

#include "Application.h"
#include "RotatingObject.h"

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

void GameObject::DrawRootGameObjects()
{
	for (auto gameObject : _rootGameObjects)
	{
		gameObject->Draw();
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

}

