#include "MovableObjectButton.h"

void core::MovableObjectButton::Update()
{
	if(_movableObject.expired()) return;
	auto movableObject = _movableObject.lock();
	if (movableObject->GetState()==MovableObject::BeingPlaced)
	{
		_strokeColor = _selectedStrokeColor;
	}
	else
	{
		_strokeColor = _regularStrokeColor;
	}
	Button::Update();
}

void core::MovableObjectButton::OnClickUp()
{
	Button::OnClickUp();
	if (_movableObject.expired()) return;
	auto movableObject = _movableObject.lock();
	movableObject->OnClickPressed(true);
}
