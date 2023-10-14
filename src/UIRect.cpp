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

		POINT cursor = Application::GetInstance().GetCursorPosition();

		auto halfBounds = 0.5f * _rect;

		if (!(cursor.x >= position._x - halfBounds._x && cursor.x <= position._x + halfBounds._x &&
			cursor.y >= position._y - halfBounds._y && cursor.y <= position._y + halfBounds._y)) 
		{
			if (_hovered)
			{
				_hovered = false;
				OnEndHover();
			}
			return;
		}

		OnHover();

		//Check if cursor is clicked
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
			OnCickDown();
			_clicked = true;
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


		if (!_stroke) return;
		auto halfBounds = 0.5f * _rect;
		DrawLine(GetWorldPosition()-halfBounds, GetWorldPosition() + Vector2(halfBounds._x,-halfBounds._y), _strokeColor);
		DrawLine(GetWorldPosition()-halfBounds, GetWorldPosition() + Vector2(-halfBounds._x, halfBounds._y), _strokeColor);
		DrawLine(GetWorldPosition() + Vector2(halfBounds._x, -halfBounds._y), GetWorldPosition() + halfBounds, _strokeColor);
		DrawLine(GetWorldPosition() + Vector2(-halfBounds._x, halfBounds._y), GetWorldPosition() + halfBounds, _strokeColor);

	}
}
