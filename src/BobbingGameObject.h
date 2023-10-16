#pragma once
#include "GameObject.h"
#include "Lerper.h"
namespace core {
	class BobbingGameObject :
		public GameObject
	{
	public:
		float _rotation1;
		float _rotation2;
		int _numberOfSteps;
		int _currentStep = 0;

		Lerper _lerper;

		BobbingGameObject(float rotation1, float rotation2, int numberOfSteps) : _rotation1(rotation1), _rotation2(rotation2), _numberOfSteps(numberOfSteps)
			, _lerper(Lerper(rotation1, rotation2, numberOfSteps, Lerper::LerpCurve::Smooth, Lerper::LerpLoop::PingPong))
		{};

		virtual void Update() override;
	};
}


