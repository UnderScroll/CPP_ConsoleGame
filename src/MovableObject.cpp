#include "MovableObject.h"
#include "Application.h"

namespace core 
{
	void MovableObject::Update()
	{
		if (_state == States::BeingPlaced)
		{
			SetWorldPosition(Vector2(Application::GetInstance().GetCursorPosition()));
		}
		if (Application::GetClickPressed)
		{
				OnClickPressed();
		}
	}
}