#include "Button.h"
namespace core
{
	void Button::OnHover()
	{
		ComputeColor();
	}
	void Button::OnEndHover()
	{
		ComputeColor();
	}

	void Button::OnClickDown()
	{
		ComputeColor();
	}

	void Button::OnClickUp()
	{
		ComputeColor();
	}

	void Button::ComputeColor()
	{
		if (GetClicked())
		{
			_fillColor = _clickColor;
			return;
		}

		if (GetHovered()) {
			_fillColor = _hoverColor;
			return;
		}
		
		_fillColor = _regularColor;
	}
}