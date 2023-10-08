#include "GameObject.h"

#include "Application.h"

namespace core {

std::vector<GameObject*> GameObject::gameObjects = std::vector<GameObject*>();

GameObject::GameObject() {
	Application::ofstream << "[INFO] GameObject Constructor : " << this << std::endl;
	gameObjects.push_back(this);
}

GameObject::~GameObject() {
	Application::ofstream << "[INFO] GameObject Destructor : " << this << std::endl;
	auto this_it = std::find(gameObjects.begin(), gameObjects.end(), this);
	if (this_it != gameObjects.end())
		gameObjects.erase(this_it);
}

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

	_localPosition = GetWorldPosition();
	_parent = nullptr;
}

void GameObject::AddChild(std::shared_ptr<GameObject> newChildPtr)
{
	if (newChildPtr->_parent != nullptr)
	{
		throw std::runtime_error("Tried to add a child that already had a parent to a game object. If you want to change the parent of a game object your must call DetachFromParent first.");
	}
	//Change the local position of the new child so that it can stay at the same position in the world even though it now has a parent.
	newChildPtr->SetLocalPosition(newChildPtr->GetWorldPosition() - GetWorldPosition());

	newChildPtr->_parent = shared_from_this();

	_children.push_back(newChildPtr);
}

}

