#pragma once

#include "GameObject.h"

namespace core
{
	/*
	Utility class for rectangular UI elements
	Used for buttons
	*/
	class UIRect :
		public GameObject
	{
	public:
		Vector2 _rect;
		Color _fillColor;
		double _alpha;

		enum FillType {
			NoFill,
			RegularFill,
			BackgroundFill
		};


		bool _stroke = true;
		Color _strokeColor=BLACK;
		FillType _fillType=FillType::RegularFill;

		bool _isHoveredCheck=false; //If false, the object won't check if he is hovered or clicked

		virtual void OnHover() {};
		virtual void OnEndHover() {};
		bool GetHovered() const { return _hovered; };

		virtual void OnClickDown() {};
		virtual void OnClickUp() {} ;
		bool GetClicked() const { return _clicked; };

		virtual void Update() override;
		virtual void Draw() override;
		UIRect(Vector2 rect, Color fillColor, Color strokeColor=BLACK, bool stroke = true,  FillType fillType=FillType::RegularFill, double alpha = 1) : _rect(rect), _fillColor(fillColor), _stroke(stroke),_strokeColor(strokeColor), _fillType(fillType), _alpha(alpha)
		{
			_layer=Layer::UI;
		};

	private:
		bool _hovered = false;
		bool _clicked = false;
	};
}


