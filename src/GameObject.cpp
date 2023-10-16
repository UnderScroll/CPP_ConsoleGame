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
				itr=r_game_objects.erase(itr);
			}
		}

		for (int i=0;i<r_game_objects.size();++i)
		{
			auto r_game_object=r_game_objects[i];

			if(!(r_game_object)->_enabled) continue;

			(r_game_object)->Update();
		}
	}

	void GameObject::Draw()
	{
		for (auto child : _children)
		{
			if(!child->_enabled) continue;
			child->Draw();
		}
	}

	void GameObject::DrawRootGameObjects()
	{
		for (int i = 0; i < LAYERS_COUNT; ++i)
		{
			auto layer = LAYERS[i];
			for (auto gameObject : _rootGameObjects)
			{
				if (!gameObject->_enabled) continue;
				if (gameObject->_layer != layer) continue;
				gameObject->Draw();
			}
		}
	}

	Vector2 GameObject::GetBoundingBox()
	{
		Vector2 biggestBoundingBox=Vector2();
		for (auto child : _children) {
			if (child->GetBoundingBox().SqrMagnitude() > biggestBoundingBox.SqrMagnitude()) {
				biggestBoundingBox = child->GetBoundingBox();
			}
		}
		return biggestBoundingBox;
	}

	float GameObject::GetDiameter()
	{
		return GetBoundingBox().Magnitude();
	}

	Vector2 GameObject::GetWorldPosition() const
	{
		if (_parent.expired()) return GetLocalPosition();
		auto parent = _parent.lock();
		auto rotatedLocalPosition = (parent->GetLocaleScale() * GetLocalPosition()).RotateByRadians(parent->GetWorldRotationInRadians());
		return rotatedLocalPosition + parent->GetWorldPosition();
	}

	Vector2 GameObject::GetWorldScale() const
	{
		if (_parent.expired()) return GetLocaleScale();
		auto parent = _parent.lock();
		return GetLocaleScale() * parent->GetWorldScale();
	}

	void GameObject::SetLocalScale(Vector2 targetScale)
	{
		_localScale = targetScale;
		for (auto child : _children) {
			//Recalculate variables suposed to be recalculated when the piece is rotated
			child->SetLocalScale(child->GetLocaleScale());
		}
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

