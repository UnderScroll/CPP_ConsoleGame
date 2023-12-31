#include "UIRect.h"
#include "Application.h"

namespace core
{
	void UIRect::Update()
	{
		GameObject::Update();

		//Check if cursor is hovered
		if (!_isHoveredCheck) return;
		Vector2 position = GetWorldPosition();

		Vector2 _cursor = Application::GetCursorPosition();

		auto halfBounds = 0.5f * _rect;

		if (!(_cursor._x >= position._x - halfBounds._x && _cursor._x <= position._x + halfBounds._x &&
			_cursor._y >= position._y - halfBounds._y && _cursor._y <= position._y + halfBounds._y)) 
		{
			if (_hovered)
			{
				_hovered = false;
				_clicked = false;
				OnEndHover();
			}
			return;
		}

		if (!_hovered) {
			_hovered = true;
			OnHover();
		}
		
		//Check if cursor is clicked
		if (core::Application::GetClickDown())
		{
			_clicked = true;
			OnClickDown();	
			return;
		}

		if (_clicked)
		{
			_clicked = false;
			OnClickUp();
		}
	}

	void UIRect::Draw()
	{
		if (_fillType != FillType::NoFill) {
			auto halfBounds = 0.5f * _rect;
			Drawable::DrawRectangle(GetWorldPosition() - halfBounds, GetWorldPosition() + halfBounds, _fillColor, _alpha, !_stroke, _fillType == FillType::BackgroundFill);
		}


		if (!_stroke) {
			GameObject::Draw();
			return;
		}

		auto halfBounds = 0.5f * _rect;
		DrawLine(GetWorldPosition()-halfBounds, GetWorldPosition() + Vector2(halfBounds._x,-halfBounds._y), _strokeColor);
		DrawLine(GetWorldPosition()-halfBounds, GetWorldPosition() + Vector2(-halfBounds._x, halfBounds._y), _strokeColor);
		DrawLine(GetWorldPosition() + Vector2(halfBounds._x, -halfBounds._y), GetWorldPosition() + halfBounds, _strokeColor);
		DrawLine(GetWorldPosition() + Vector2(-halfBounds._x, halfBounds._y), GetWorldPosition() + halfBounds, _strokeColor);

		GameObject::Draw();
	}
}
