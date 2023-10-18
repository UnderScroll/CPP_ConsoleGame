#pragma once
#include "GameObject.h"
#include "Lerper.h"
namespace core {
	class BobbingGameObject :
		public GameObject
	{
	public:
		double _rotation1;
		double _rotation2;
		Vector2 _posModifier1;
		Vector2 _posModifier2;
		Vector2 _unmodifierPos;
		
		int _numberOfSteps;
		int _currentStep = 0;

		Lerper _rotationLerper;
		Lerper _posXLerper;
		Lerper _posYLerper;

		BobbingGameObject(double rotation1, double rotation2, int numberOfSteps) : BobbingGameObject(rotation1, rotation2, Vector2(0, 0), Vector2(0, 0), numberOfSteps)
		{}

		BobbingGameObject(double rotation1, double rotation2, Vector2 pos1, Vector2 pos2, int numberOfSteps) : _rotation1(rotation1), _rotation2(rotation2), _posModifier1(pos1), _posModifier2(pos2), _numberOfSteps(numberOfSteps)
			, _rotationLerper(Lerper(rotation1, rotation2, numberOfSteps, Lerper::LerpCurve::Smooth, Lerper::LerpLoop::PingPong)), 
			_posXLerper(Lerper(pos1._x, pos2._x, numberOfSteps, Lerper::LerpCurve::Smooth, Lerper::LerpLoop::PingPong)),
				_posYLerper(Lerper(pos1._y, pos2._y, numberOfSteps, Lerper::LerpCurve::Smooth, Lerper::LerpLoop::PingPong))
		{};

		virtual void Update() override;
		virtual void SetLocalPosition(Vector2 targetPosition) override {
			_unmodifierPos = targetPosition;
			_localPosition=(targetPosition+Vector2(_posXLerper.GetValue(_currentStep),_posYLerper.GetValue(_currentStep)));
		}
	};
}


