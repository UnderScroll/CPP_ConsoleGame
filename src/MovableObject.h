#pragma once
#include "GameObject.h"

#include "Polygon.h"

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

		void OnNewChild(std::shared_ptr<GameObject> child) override
		{
			GameObject::OnNewChild(child);
			ComputeDiameter();
		};

		virtual void OnCreationOver() override;

	private:
		States _state = Placed;
		bool _hover;
		float _diameter;
		std::weak_ptr<GameObject> _movePrompt;
		void ComputeDiameter();
		bool IsCursorInRange();
	};
}

