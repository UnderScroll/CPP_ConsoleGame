#include "MovableObject.h"

#include "Application.h"
#include "TextObject.h"
#include "SoundManager.h"

namespace core
{
	void MovableObject::OnCreationOver()
	{
		Polygon movePromptsPolygons[]{
			Polygon(
				{
					Vector2(0, 1.5),
					Vector2(1, 0.75),
					Vector2(1, -0.75),
					Vector2(0, -1.5),
					Vector2(-1, -0.75),
					Vector2(-1, 0.75)
				}
				, true, Drawable::GRAY, 0.5f,Vector2(0,-3),Vector2(4,4)), //Mouse
			Polygon(
				{
					Vector2(1, -0.75),
					Vector2(0, -1.5),
					Vector2(0, -0.75),
				}
				, true, Drawable::GRAY, 0.5f,Vector2(0,-3),Vector2(4,4)), //Right click
			Polygon(
				{
					Vector2(-1, -0.75),
					Vector2(0, -1.5),
					Vector2(0, -0.75),
				}
				, true, Drawable::RED, 0.5f,Vector2(0,-3),Vector2(4,4)), //Left click

			//Cross with arrows:
			Polygon(
				{
					Vector2(-0.8,-0.2),
					Vector2(-1,0),
					Vector2(-0.8,0.2),
					Vector2(-1,0),

					Vector2(1,0),
					Vector2(0.8,-0.2),
					Vector2(1,0),
					Vector2(0.8,0.2),
					Vector2(1,0),

					Vector2(0,0),

					Vector2(0,1),
					Vector2(-0.2,0.8),
					Vector2(0,1),
					Vector2(0.2,0.8),
					Vector2(0,1),

					Vector2(0,-1),
					Vector2(-0.2,-0.8),
					Vector2(0,-1),
					Vector2(0.2,-0.8),
					Vector2(0,-1),
				}
				, false, Drawable::GRAY, 0.5f,Vector2(0,3),Vector2(5,5)), //Left click
		};

		_movePrompt = AddChild<GameObject>(GameObject());
		auto movePrompt = _movePrompt.lock();
		movePrompt->SetLocalScale(Vector2(2, 2));
		for (auto pol : movePromptsPolygons) {
			movePrompt->AddChild<Polygon>(pol);
		}

		Polygon rotatePromptsPolygons[]{
			Polygon(
				{
					Vector2(-0.5, -0.5),
					Vector2(0.5, -0.5),
					Vector2(0.5, 0.5),
					Vector2(-0.5, 0.5),
				}
				, true, Drawable::GRAY, 0.5f,Vector2(-2.8f,0),Vector2(9,9)), //Q/A key

			Polygon(
				{
					Vector2(0.3, -0.3),
					Vector2(-0.3, 0.3),
				}
				, true, Drawable::GRAY, 0.5f,Vector2(-2.8f,0),Vector2(9,9)), // Slash

			Polygon(TextObject::GetPointsForLetter('Q',2), false, Drawable::RED, 0.5f,Vector2(-2.8f - 0.6f,-0.6f),Vector2(3,3)), //Q letter2
			Polygon(TextObject::GetPointsForLetter('Q',3), false, Drawable::RED, 0.5f,Vector2(-2.8f - 0.6f,-0.6f),Vector2(3,3)), //Q letter part 2

			Polygon(TextObject::GetPointsForLetter('A'), false, Drawable::RED, 0.5f,Vector2(-2.8f + 1.0f,+0.8f),Vector2(2.5,4)), //A

			Polygon(
				{
					Vector2(-0.5, -0.5),
					Vector2(0.5, -0.5),
					Vector2(0.5, 0.5),
					Vector2(-0.5, 0.5),
				}
				, true, Drawable::GRAY, 0.5f,Vector2(2.8f,0),Vector2(9,9)), //D key

			Polygon(TextObject::GetPointsForLetter('D'), false, Drawable::RED, 0.5f,Vector2(2.8f,0),Vector2(4,6)), //D

			//Half circle with arrows:
			Polygon(
				{
					Vector2(-1, 0),
					Vector2(-0.8, -0.2),
					Vector2(-1, 0),
					Vector2(-1.2, -0.2),
					Vector2(-1, 0),

					Vector2(-1,-0.3),
					Vector2(-0.75, -0.75),
					Vector2(0, -1),
					Vector2(0.75, -0.75),
					Vector2(1, -0.3),

					Vector2(1, 0),
					Vector2(0.8, -0.2),
					Vector2(1,0),
					Vector2(1.2, -0.2)
				}
				, false, Drawable::GRAY, 0.5f,Vector2(0,-3),Vector2(7,7)),
		};

		_rotatePrompt = AddChild<GameObject>(GameObject());
		auto rotatePrompt = _rotatePrompt.lock();
		rotatePrompt->SetLocalScale(Vector2(2, 2));
		for (auto pol : rotatePromptsPolygons) {
			rotatePrompt->AddChild<Polygon>(pol);
		}
	}

	void MovableObject::Update()
	{
		GameObject::Update();
		if (_state == States::BeingPlaced)
		{
			SetWorldPosition(Application::GetInstance().GetCursorPosition());
		}
		if (Application::GetClickPressed())
		{
			OnClickPressed();
		}
		_hover = IsCursorInRange();

		if (_hover)
		{
			for (auto& child : _children) {
				if (!_movePrompt.expired()) {
					if (_movePrompt.lock() == child) continue;
				}
				if (!_rotatePrompt.expired()) {
					if (_rotatePrompt.lock() == child) continue;
				}
				if (Application::GetHorizontalAxis() != 0) {
					SoundManager::PlayRotateSound();
				}
				child->RotateByDegrees(_rotationSpeed * Application::GetHorizontalAxis());
			}
		}

		if (Application::GetHorizontalAxis() != 0 || _state == States::BeingPlaced)
		{
			for (auto& child : _children) {
				std::shared_ptr<Polygon> pol = std::dynamic_pointer_cast<Polygon>(child);

				if (!pol) continue;

				auto polValue = Polygon();

				polValue._points = pol->_computedPointsWorldPositions;
				polValue._computedPointsWorldPositions = pol->_computedPointsWorldPositions;
				polValue._isClosed = pol->_isClosed;
				
				Laser::s_colliders[_colliderIndex] = Collider(polValue, Collider::Wall, true);
				break;
			}
		}

		if (_movePrompt.expired()) return;

		auto movePrompt = _movePrompt.lock();
		movePrompt->_enabled = _hover && _state != BeingPlaced;
		movePrompt->_enabled &= !_canOnlyRotate;

		if (_rotatePrompt.expired()) return;

		auto rotatePrompt = _rotatePrompt.lock();
		rotatePrompt->_enabled = _hover;
	}

	void MovableObject::Draw()
	{
		ComputeRotatePromptsPosition();

		GameObject::Draw();

		//Iterate through the children until it finds the one that is a polygon
		for (auto& child : _children) {
			std::shared_ptr<Polygon> pol = std::dynamic_pointer_cast<Polygon>(child);

			if (!pol) continue;
			//iterate on _computedPointsWorldPositions
			for (int i = 0; i < pol->_computedPointsWorldPositions.size(); i++) {
				Application::ofstream << "WorldX of point" << i << " = " << pol->_computedPointsWorldPositions[i]._x << std::endl;
			}

			break;
		}
	}

	void MovableObject::OnClickPressed(bool forceCursorInRange)
	{
		if (_canOnlyRotate)
			return;

		if (_state == States::BeingPlaced)
		{
			SoundManager::PlayClickSound();
			_state = States::Placed;
		}
		else if (_state == States::Placed && (forceCursorInRange || IsCursorInRange()))
		{
			SoundManager::PlayClickSound();
			_state = States::BeingPlaced;
		}	
	}

	void MovableObject::ComputeDiameter()
	{
		float maxDiameter = 0;
		for (auto child : _children)
		{
			if (child == _movePrompt.lock() || child == _rotatePrompt.lock()) continue;
			maxDiameter = max(maxDiameter, child->GetDiameter());
		}
		_diameter = maxDiameter;

		if (_movePrompt.expired()) return;
		_movePrompt.lock()->SetLocalPosition({ -0.5f * _diameter - 18,0 });
	}

	void MovableObject::ComputeRotatePromptsPosition() {
		float maxHeight = 0;
		for (auto child : _children)
		{
			if (child == _movePrompt.lock() || child == _rotatePrompt.lock()) continue;
			maxHeight = max(maxHeight, child->GetBoundingBox()._y);
		}

		if (_rotatePrompt.expired()) return;
		_rotatePrompt.lock()->SetLocalPosition({ 0, -0.5f * maxHeight - 18 });
	}

	bool MovableObject::IsCursorInRange()
	{
		return ((Application::GetCursorPosition() - GetWorldPosition()).SqrMagnitude() < (0.5 * _diameter * 0.5 * _diameter));
	}
}