#pragma once
#include "Button.h"

namespace core {
	class NextLevelButton :
		public Button
	{
		public:
			NextLevelButton(Vector2 rect, Color regularColor, Color hoverColor, Color clickColor, Color strokeColor = BLACK, bool stroke = true, FillType fillType = FillType::RegularFill, double alpha = 1) :
				Button(rect, regularColor, hoverColor, clickColor, strokeColor, stroke, fillType, alpha)
			{};
			virtual void OnClickUp() override;
	};
}


