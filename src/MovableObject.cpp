#include "MovableObject.h"
#include "Application.h"

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

					Vector2(0,-1),
					Vector2(-0.2,-0.8),
					Vector2(0,-1),
					Vector2(-0.2,1.2),
					Vector2(0,-1),

					Vector2(-1,0),

					Vector2(0,1),
					Vector2(-0.2,0.8),
					Vector2(0,1),
					Vector2(-0.2,1.2),				
				}
				, false, Drawable::GRAY, 0.5f,Vector2(0,3),Vector2(5,5)), //Left click
		};

		_movePrompt = AddChild<GameObject>(GameObject());
		auto movePrompt = _movePrompt.lock();
		movePrompt->SetLocalScale(Vector2(2, 2));
		for (auto pol : movePromptsPolygons) {
			movePrompt->AddChild<Polygon>(pol);
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
		if (_movePrompt.expired()) return;

		auto movePrompt= _movePrompt.lock();

		movePrompt->_enabled = _hover;
	}

	void MovableObject::Draw()
	{
		GameObject::Draw();
		if (_state == States::BeingPlaced)
		{
			return;
		}
	}

	void MovableObject::OnClickPressed()
	{
		if (_state == States::BeingPlaced)
		{
			_state = States::Placed;
		}
		else if (_state == States::Placed && IsCursorInRange())
		{
			_state = States::BeingPlaced;
		}
	}

	void MovableObject::ComputeDiameter()
	{
		float maxDiameter = 0;
		for (auto child : _children)
		{
			std::shared_ptr<Polygon> polygonObj = std::dynamic_pointer_cast<Polygon>(child);

			if (!polygonObj) continue;

			maxDiameter = max(maxDiameter, polygonObj->GetDiameter());
		}
		_diameter = maxDiameter;
		if (_movePrompt.expired()) return;
		_movePrompt.lock()->SetLocalPosition({ -0.5f * _diameter-10,0 });
	}

	bool MovableObject::IsCursorInRange()
	{
		return ((Application::GetCursorPosition() - GetWorldPosition()).SqrMagnitude() < (0.5 * _diameter * 0.5 * _diameter));
	}
}