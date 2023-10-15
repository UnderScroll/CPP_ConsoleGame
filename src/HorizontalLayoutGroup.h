#pragma once
#include "UIRect.h"
namespace core {
	class HorizontalLayoutGroup :
		public UIRect
	{
		public:
			float _spacing;
			HorizontalLayoutGroup(Vector2 rect, float spacing, Color fillColor, Color strokeColor = BLACK, bool stroke = true, FillType fillType = FillType::RegularFill, float alpha = 1) :
				UIRect(rect, fillColor, strokeColor, stroke, fillType, alpha), _spacing(spacing)
			{
			_layer = Layer::UI;
			_elements = std::vector<std::shared_ptr<UIRect>>();
		};
		
		template<typename T>
		std::shared_ptr<T> AddElement(T uiRect) 
		{
			int count = _elements.size() + 1;

			auto newElemPTr= AddChild<T>(uiRect);

			_elements.push_back(newElemPTr);

			for (int i=0; i < _elements.size();i++){
				auto element = _elements[i];
				float width= (_rect._x / count) - _spacing;
				element->_rect._x = width;
				element->SetLocalPosition(Vector2(-0.5*_rect._x+(i+0.5)*(_rect._x/count), 0));
			}
			
			return newElemPTr;
		}

		virtual void Draw() override;

	private:
		std::vector <std::shared_ptr<UIRect>> _elements;
	};
}


