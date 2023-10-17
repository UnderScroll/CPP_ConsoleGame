#include "SoundManager.h"

#include <windows.h>
#pragma comment(lib, "winmm.lib")

namespace core {
#pragma region Generic functions
	LPWSTR ConvertToLPWSTR(const std::string& s)
	{
		LPWSTR ws = new wchar_t[s.size() + 1]; // +1 for zero at the end
		copy(s.begin(), s.end(), ws);
		ws[s.size()] = 0; // zero at the end
		return ws;
	}

	void SoundManager::StartLoop(SoundEffect soundEffect)
	{
		if (_currentLoop == soundEffect) return;
		PlaySound(ConvertToLPWSTR(soundEffect.filepath.c_str()), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP | SND_NODEFAULT);
		_currentLoop = soundEffect;
	}

	void SoundManager::StopLoop(SoundEffect soundEffect)
	{
		//The loop is already stopped as there can only be one loop at the time
		//And we dont want to stop the current loop
		if (soundEffect != _currentLoop) {
			StopAllLoops();
		}
	}

	void SoundManager::StopAllLoops()
	{
		PlaySound(NULL, NULL, 0);
		_currentLoop = SoundEffect();
	}

	void SoundManager::PlaySoundEffect(SoundEffect soundEffect, bool stopPrevious)
	{
		if (stopPrevious) {
			mciSendStringA(("stop " + soundEffect.filepath).c_str(), NULL, 0, NULL);
		}
		
		mciSendStringA(("play " + soundEffect.filepath).c_str(), NULL, 0, NULL);
	}

#pragma endregion
	SoundEffect SoundManager::_currentLoop = SoundEffect();
	const SoundEffect SoundManager::_clickSound = SoundEffect("res/sounds/click.wav");
	const SoundEffect SoundManager::_rotateSound = SoundEffect("res/sounds/rotatingObjectLoop.wav");
	const SoundEffect SoundManager::_nextLevelSound = SoundEffect("res/sounds/nextLevel2.wav");
	const std::vector<SoundEffect> SoundManager::_laserSounds = { 
		SoundEffect("res/sounds/laser/laser1.wav"),
		SoundEffect("res/sounds/laser/laser2.wav"),
		SoundEffect("res/sounds/laser/laser3.wav"),
		SoundEffect("res/sounds/laser/laser4.wav"),
		SoundEffect("res/sounds/laser/laser5.wav"),
		SoundEffect("res/sounds/laser/laser6.wav"),
		SoundEffect("res/sounds/laser/laser7.wav"),
		SoundEffect("res/sounds/laser/laser8.wav"),
	};

	void SoundManager::PlayClickSound()
	{
		PlaySoundEffect(_clickSound);
	}

	void SoundManager::PlayRotateSound()
	{
		PlaySoundEffect(_rotateSound,false);
	}

	void SoundManager::PlayNextLevelSound()
	{
		PlaySoundEffect(_nextLevelSound);
	}
	void SoundManager::PlayLaserSound(int numberOfCollisions)
	{
		if(numberOfCollisions < 0)
			numberOfCollisions = 0;

		if(numberOfCollisions >= _laserSounds.size())
			numberOfCollisions = _laserSounds.size() - 1;

		PlaySoundEffect(_laserSounds[numberOfCollisions]);
	}
}