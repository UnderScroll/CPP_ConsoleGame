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
	bool _enabled=true; //When false, the application will not update it nor draw it
	std::weak_ptr<GameObject> _parent = std::weak_ptr<GameObject>();

	Color _color;
	double _alpha=1;

	template <typename T>
	static std::shared_ptr<T> AddGameObjectToRoot(T gameObject)
	{
		auto newObject = std::make_shared<T>(gameObject);
		_rootGameObjects.push_back(newObject);
		newObject->OnCreationOver();
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

	virtual Vector2 GetBoundingBox();
	virtual double GetDiameter();

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

	virtual void SetWorldPosition(Vector2 targetPosition) 
	{
		Vector2 deltaPosition=targetPosition - GetWorldPosition();
		MoveBy(deltaPosition);
	}

	virtual void SetLocalScale(Vector2 targetScale);

	virtual double GetLocalRotationInRadians()
	{
		return _localRotation;
	}

	virtual  double GetLocalRotationInDegrees()
	{
		return GetLocalRotationInRadians() * RAD_TO_DEG;
	}

	double GetWorldRotationInRadians();

	double GetWorldRotationInDegrees();

	void RotateByRadians(double deltaAngle)
	{
		RotateToRadians(_localRotation + deltaAngle);
	}

	void RotateByDegrees(double deltaAngle)
	{
		RotateByRadians(deltaAngle * DEG_TO_RAD);
	}

	virtual void RotateToRadians(double targetAngle);

	void RotateToDegrees(double targetAngle)
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

	virtual void OnNewChild(std::shared_ptr<GameObject>) {};

	template <typename T>
	std::shared_ptr<T> AddChild(T gameObject)
	{
		gameObject._parent = shared_from_this();
		gameObject.SetLocalPosition(gameObject.GetWorldPosition() - GetWorldPosition());

		auto ptr = std::make_shared<T>(gameObject);
		
		//Change the local position of the new child so that it can stay at the same position in the world even though it now has a parent.
		_children.push_back(ptr);

		OnNewChild(ptr);
		ptr->OnCreationOver();

		return ptr;
	}

	//This function is called when the object is created. It is called after the constructor and before the first call to Update()
	//It exists in case you want to add child to an object on its creation, you can't do that in the constructor because the shared_ptr is not yet initialized so shared_from_this just crasg everything
	virtual void OnCreationOver() {};

	std::vector<std::shared_ptr<GameObject>> _children;

	static std::vector<std::shared_ptr<GameObject>> _rootGameObjects;
protected:
	Vector2 _localPosition = { 0, 0 };
	Vector2 _localScale = { 1, 1 };
	//In radians
	double _localRotation = 0;
};

}
