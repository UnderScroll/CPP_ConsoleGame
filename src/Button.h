#pragma once
#include "UIRect.h"

namespace core
{
	/*
	A UI button
	used for the placable reflective surfaces and menu elements
	*/
	class Button :
		public UIRect
	{
	public:
		Color _regularColor;
		Color _hoverColor;
		Color _clickColor;
		virtual void OnHover() override;
		virtual void OnEndHover() override;
		virtual void OnClickDown() override;
		virtual void OnClickUp() override;

		Button(Vector2 rect, Color regularColor, Color hoverColor, Color clickColor, Color strokeColor = BLACK, bool stroke = true, FillType fillType = FillType::RegularFill, double alpha = 1) :
			UIRect(rect, regularColor, strokeColor, stroke, fillType, alpha), _hoverColor(hoverColor), _clickColor(clickColor)
		{
			_regularColor = _fillColor;
			_isHoveredCheck = true;
		};
	private:
		void ComputeColor();
	};

}

