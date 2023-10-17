#include "SoundManager.h"
#include <irrKlang.h>
#include <windows.h>
#pragma comment(lib, "irrKlang.lib")

namespace core {
	using namespace irrklang;
#pragma region Generic functions
	void SoundManager::StartLoop(SoundEffect soundEffect)
	{
		if (!_isInitialized)
			Initialize();
	}

	void SoundManager::StopLoop(SoundEffect soundEffect)
	{
		if (!_isInitialized)
			Initialize();
	}

	void SoundManager::StopAllLoops()
	{
		if (!_isInitialized)
			Initialize();
	}

	void SoundManager::PlaySoundEffect(SoundEffect soundEffect, bool allowOverlap)
	{
		if(!_isInitialized)
			Initialize();
		if (!allowOverlap && _engine->isCurrentlyPlaying(soundEffect.filepath.c_str()))
		{
			return;
		}
		_engine->play2D(soundEffect.filepath.c_str());
	}

	void SoundManager::Initialize()
	{
		if(_isInitialized)
			return;

		_engine = createIrrKlangDevice();

		_isInitialized = true;
	}	

#pragma endregion
	irrklang::ISoundEngine* SoundManager::_engine;
	bool SoundManager::_isInitialized = false;

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