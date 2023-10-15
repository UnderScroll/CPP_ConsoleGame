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
				, true, Drawable::WHITE, 0.5f),
		};

		_movePrompt=AddChild<GameObject>(GameObject());
		auto movePrompt = _movePrompt.lock();
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
		if(_movePrompt.expired()) return;
		_movePrompt.lock()->_enabled  =_hover;
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
	}

	bool MovableObject::IsCursorInRange()
	{
		return ((Application::GetCursorPosition() - GetWorldPosition()).SqrMagnitude() < (0.5*_diameter * 0.5*_diameter));
	}
}