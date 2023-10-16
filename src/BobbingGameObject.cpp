#include "BobbingGameObject.h"
namespace core {
	void BobbingGameObject::Update()
	{
		_currentStep++;
		if (_currentStep > 2*_numberOfSteps) {
			_currentStep = 0;
		}
		RotateToDegrees(_lerper.GetValue(_currentStep));
		GameObject::Update();
	}
}