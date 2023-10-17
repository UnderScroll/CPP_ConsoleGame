#include "Level.h"

#include "Collider.h"
#include "HorizontalLayoutGroup.h"
#include "Polygon.h"
#include "UIRect.h"
#include "Console.h"
#include "TextObject.h"
#include "MovableObject.h"
#include "MovableObjectButton.h"

namespace core {
	void Level::LoadLevel()
	{
		if (_bottomHudOn) {
			_bottomHud = GameObject::AddGameObjectToRoot<HorizontalLayoutGroup>(HorizontalLayoutGroup(Vector2((WIDTH / 2) + 2, 24), 10, Drawable::Color::BLACK, Drawable::Color::WHITE, true, UIRect::BackgroundFill));
			_bottomHud->SetLocalPosition({ WIDTH / 4 - 1, HEIGHT - 12 });
		}
		if (_topHudOn) {
			_topHud = GameObject::AddGameObjectToRoot<HorizontalLayoutGroup>(HorizontalLayoutGroup(Vector2((WIDTH / 2) + 2, 5), 10, Drawable::Color::BLACK, Drawable::Color::WHITE, false, UIRect::NoFill));
			_topHud->SetLocalPosition({ WIDTH / 4 - 1, 10 });
			auto namePtr = _topHud->AddChild<TextObject>(TextObject(Drawable::WHITE, 1,1));
			namePtr->SetText(_levelName);
			namePtr->SetLocalScale({ 3,3 });
			namePtr->SetLocalPosition({ 0,-6 });
		}

		size_t movableElementColliderIndex = 0;
		for (Polygon& pol : _movableElements)
		{
			auto movablElementPtr=GameObject::AddGameObjectToRoot<MovableObject>(MovableObject());
			movablElementPtr->SetLocalPosition(pol.GetLocalPosition());
			auto polPtr = movablElementPtr->AddChild<Polygon>(pol);
			polPtr->SetLocalPosition(Vector2(0, 0));
			
			auto buttonPtr=_bottomHud->AddElement<MovableObjectButton>(MovableObjectButton(Vector2(0,20), Drawable::Color::WHITE, Drawable::LIGHTER_WHITE, Drawable::GRAY, movablElementPtr, Drawable::Color::BLACK, Drawable::Color::CYAN, true, UIRect::BackgroundFill));
			buttonPtr->SetPreview(pol, Drawable::BLACK);

			movablElementPtr->_colliderIndex = movableElementColliderIndex++;
			Laser::s_colliders.push_back(Collider(pol, Collider::Wall, true));
		}

		for (Polygon& pol : _rotatableElements) {
			auto movablElementPtr = GameObject::AddGameObjectToRoot<MovableObject>(MovableObject());
			movablElementPtr->SetLocalPosition(pol.GetLocalPosition());
			auto polPtr = movablElementPtr->AddChild<Polygon>(pol);

			movablElementPtr->_colliderIndex = movableElementColliderIndex++;
			Laser::s_colliders.push_back(Collider(pol, Collider::Wall, true));
		}

		for (Polygon& pol : _staticNonReflectivesElements) {
			auto polPtr = GameObject::AddGameObjectToRoot<Polygon>(pol);
			Laser::s_colliders.push_back(Collider(pol, Collider::Wall, false));
		}

		for (Polygon& pol : _staticReflectivesElements) {
			auto polPtr = GameObject::AddGameObjectToRoot<Polygon>(pol);
			Laser::s_colliders.push_back(Collider(pol, Collider::Wall, true));
		}

		for (Laser& laser : _lasers) {
			auto movablElementPtr = GameObject::AddGameObjectToRoot<MovableObject>(MovableObject());
			movablElementPtr->_canOnlyRotate = true;
			movablElementPtr->SetLocalPosition(laser._position);
			auto polPtr = movablElementPtr->AddChild<Laser>(laser);

			//Laser::s_colliders.push_back(Collider(laser._laserBase, Collider::Wall, false));
		}

		GameObject::AddGameObjectToRoot<Polygon>(_sensor._collisionShape);
		Laser::s_colliders.push_back(_sensor);	
	}

	void Level::ClearCurrentLevel()
	{
		for (auto rootGameObject : GameObject::_rootGameObjects) {
			rootGameObject->Destroy();
		}
		GameObject::_rootGameObjects.clear();
		Laser::s_colliders.clear();
	}
}

