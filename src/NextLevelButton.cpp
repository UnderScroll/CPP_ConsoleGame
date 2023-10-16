#include "NextLevelButton.h"
#include "Application.h"
#include "SoundManager.h"

namespace core {
	void NextLevelButton::OnClickUp()
	{
		SoundManager::PlayNextLevelSound();
		Application::LoadNextLevel();
	}
}

