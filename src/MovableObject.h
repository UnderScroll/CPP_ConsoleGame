#pragma once
#include "GameObject.h"

namespace core
{
	class MovableObject:
		public GameObject
	{
	public:
		virtual void Update() override;
		virtual void Draw() override;
		enum States {
			Deactivated,
			Placed,
			BeingPlaced,
			Locked
		};
		States GetState() const { return _state; };
		void OnClickPressed();
		void OnHoverStart();
		void OnHoverEnd();
	private:
		States _state = Deactivated;
		bool _hover;
	};
}

