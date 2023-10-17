#pragma once
#include "GameObject.h"

#include "Polygon.h"

namespace core
{
	class MovableObject:
		public GameObject
	{
	public:
		enum States {
			Deactivated,
			Placed,
			BeingPlaced,
			Locked
		};

		virtual void Update() override;
		virtual void Draw() override;
		
		States GetState() const { return _state; };
		void OnClickPressed(bool forceCursorInRange = false);

		void OnNewChild(std::shared_ptr<GameObject> child) override
		{
			GameObject::OnNewChild(child);
			ComputeDiameter();
		};

		float _rotationSpeed = 3.0f; //In degrees

		size_t _colliderIndex;

		virtual void OnCreationOver() override;

		bool _canOnlyRotate = false;

	private:
		States _state = Placed;
		bool _hover;
		float _diameter;
		std::weak_ptr<GameObject> _movePrompt;
		std::weak_ptr<GameObject> _rotatePrompt;
		void ComputeDiameter();
		void ComputeRotatePromptsPosition();
		bool IsCursorInRange();
	};
}

