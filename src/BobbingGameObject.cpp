#include "BobbingGameObject.h"
namespace core {

void BobbingGameObject::Update()
{
	_currentStep++;
	if (_currentStep > 2 * _numberOfSteps) {
		_currentStep = 0;
	}
	RotateToDegrees(_rotationLerper.GetValue(_currentStep));
	_localPosition = (_unmodifierPos + Vector2(_posXLerper.GetValue(_currentStep), _posYLerper.GetValue(_currentStep)));
	GameObject::Update();
}

}