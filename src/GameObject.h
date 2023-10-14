#pragma once
#include <memory>
#include <numbers>
#include <vector>

#include "Drawable.h"

namespace core {

class GameObject :
	public Drawable,
	public std::enable_shared_from_this<GameObject>
{
	// inherited by via Drawable
public:
	bool _destroyed = false; //When true, the application will delete it from its vectors
	std::weak_ptr<GameObject> _parent = std::weak_ptr<GameObject>();

	template <typename T>
	static std::shared_ptr<T> AddGameObjectToRoot(T gameObject)
	{
		auto newObject = std::make_shared<T>(gameObject);
		_rootGameObjects.push_back(newObject);
		return newObject;
	}

	//All children of GameObject must implement a static factory method ! Sadly, there's no way to define a static virtual function :(
	//Don't forget to make all the constructor private or protected
	virtual void Update();

	void static UpdateGameObjectPointersList(std::vector<std::shared_ptr<GameObject>>& r_game_objects);

	virtual void Draw();

	void static DrawRootGameObjects();

	virtual void Destroy()
	{
		_destroyed = true;
	}

	//The function relative to position and rotation are virtual so that children can redefine them. This is useful for polygons that needs special code to run to rotate correctly
	virtual Vector2 GetLocalPosition() const
	{
		return _localPosition;
	}

	Vector2 GetWorldPosition() const;

	Vector2 GetWorldScale() const;

	Vector2 GetLocaleScale() const 
	{
		return _localScale;
	}

	virtual void MoveBy(Vector2 deltaPosition)
	{
		SetLocalPosition(_localPosition + deltaPosition);
	}

	virtual void SetLocalPosition(Vector2 targetPosition)
	{
		_localPosition = targetPosition;
	}

	virtual void SetLocalScale(Vector2 targetScale);

	virtual float GetLocalRotationInRadians()
	{
		return _localRotation;
	}

	virtual  float GetLocalRotationInDegrees()
	{
		return GetLocalRotationInRadians() * RAD_TO_DEG;
	}

	float GetWorldRotationInRadians();

	float GetWorldRotationInDegrees();

	void RotateByRadians(float deltaAngle)
	{
		RotateToRadians(_localRotation + deltaAngle);
	}

	void RotateByDegrees(float deltaAngle)
	{
		RotateByRadians(deltaAngle * DEG_TO_RAD);
	}

	virtual void RotateToRadians(float targetAngle);

	void RotateToDegrees(float targetAngle)
	{
		RotateToRadians(DEG_TO_RAD * targetAngle);
	}

	void DetachFromParent();

	void AddChild(std::shared_ptr<GameObject> newChildPtr)
	{
		//Change the local position of the new child so that it can stay at the same position in the world even though it now has a parent.
		newChildPtr->SetLocalPosition(newChildPtr->GetWorldPosition() - GetWorldPosition());

		newChildPtr->_parent = shared_from_this();

		_children.push_back(newChildPtr);
	}

	template <typename T>
	std::shared_ptr<T> AddChild(T gameObject)
	{
		gameObject._parent = shared_from_this();
		gameObject.SetLocalPosition(gameObject.GetWorldPosition() - GetWorldPosition());

		auto ptr = std::make_shared<T>(gameObject);
		
		//Change the local position of the new child so that it can stay at the same position in the world even though it now has a parent.

		_children.push_back(ptr);

		return ptr;
	}

	std::vector<std::shared_ptr<GameObject>> _children;

	static std::vector<std::shared_ptr<GameObject>> _rootGameObjects;
protected:
	Vector2 _localPosition = { 0, 0 };
	Vector2 _localScale = { 1, 1 };
	//In radians
	float _localRotation = 0;
};

}
