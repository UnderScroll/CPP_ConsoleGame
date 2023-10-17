#pragma once
#include "Button.h"
#include "MovableObject.h"

namespace core 
{
#define FAR_AWAY Vector2(100000,100000)

	class MovableObjectButton :
		public Button
	{
		public:
			MovableObjectButton(Vector2 rect, Color regularColor, Color hoverColor, Color clickColor, std::weak_ptr<MovableObject> movableObject, Color strokeColor = BLACK, Color selectedStrokeColor = GRAY, bool stroke = true, FillType fillType = FillType::RegularFill, double alpha = 1) :
				Button(rect, regularColor, hoverColor, clickColor, strokeColor, stroke, fillType, alpha), _selectedStrokeColor(selectedStrokeColor), _movableObject(movableObject) {
				_regularStrokeColor = _strokeColor;
				if (_movableObject.expired()) return;
				_movableObject.lock()->SetLocalPosition(FAR_AWAY);
			};

			virtual void Update() override;
			virtual void OnClickUp() override;

			template <typename T>
			void SetPreview(T gameObject)
			{
				double a = _rect._x / gameObject.GetBoundingBox()._x;
				double b = _rect._y / gameObject.GetBoundingBox()._y;
				//The value 0.4f was chosen using pifometrie
				double scale = std::min<double>(0.4f * a, 0.4f * b);

				auto preview = AddChild<T>(gameObject);
				preview->SetLocalPosition(Vector2(0, 0));
				preview->SetLocalScale(Vector2(scale, scale));
			}	

			template <typename T>
			void SetPreview(T gameObject, Color previewColor)
			{
				gameObject._color = previewColor;
				SetPreview<T>(gameObject);
			}
	private:
		Color _selectedStrokeColor;
		Color _regularStrokeColor;
		std::weak_ptr<MovableObject> _movableObject;
	};

}

