#pragma once
#include <memory>
#include <numbers>
#include <vector>

#include "Drawable.h"
#include "Collider.h"

class GameObject :
	public Drawable,
	public Collider,
	public std::enable_shared_from_this<GameObject>
{
	// inherited by via Drawable
public:
	bool _destroyed = false; //When true, the application will delete it from its vectors
	std::shared_ptr<GameObject> _parent = nullptr;

	//All children of GameObject must implement a static factory method ! Sadly, there's no way to define a static virtual function :(
	//Don't forget to make all the constructor private or protected
	virtual void Update();

	void static UpdateGameObjectPointersList(std::vector<std::shared_ptr<GameObject>>& r_game_objects);

	virtual void Draw();

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

	void AddChild(std::shared_ptr<GameObject> newChildPtr);

	std::vector<std::shared_ptr<GameObject>> _children;
protected:
	Vector2 _localPosition = { 0, 0 };
	Vector2 _localScale = { 1, 1 };
	//In radians
	float _localRotation = 0;
	GameObject() {}
};

