#include "NextLevelButton.h"
#include "Application.h"

namespace core {
	void NextLevelButton::OnClickUp()
	{
		Application::LoadNextLevel();
	}
}

