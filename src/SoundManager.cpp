#include "SoundManager.h"
#include <irrKlang.h>
#include <windows.h>
#pragma comment(lib, "irrKlang.lib")

namespace core {
	using namespace irrklang;
#pragma region Generic functions
	/// <summary>
	/// 
	/// </summary>
	/// <param name="soundEffect"></param>
	/// <param name="needToCreateAPointer">If true, the play2D will assign a real pointer to soundEffect.sound. Useful, but wasteful</param>
	void SoundManager::StartLoop(SoundEffect &soundEffect, bool needToCreateAPointer)
	{
		if (!_isSetup)
			Setup();

		if (soundEffect.isLooping) {
			return;
		}

		SoundManager::PlaySoundEffect(soundEffect,false,true, needToCreateAPointer);
		soundEffect.isLooping = true;
		_currentlyLooping.push_back(soundEffect);
	}

	void SoundManager::StopLoop(SoundEffect &soundEffect)
	{
		if (!_isSetup)
			Setup();

		if (!soundEffect.isLooping) {
			return;
		}

		_engine->stopAllSoundsOfSoundSource(soundEffect.soundSource);
		soundEffect.sound->drop();

		//Remove the sound source from the _currentlyLooping ones
		for (int i = 0; i < _currentlyLooping.size(); i++)
		{
			if (_currentlyLooping[i].soundSource == soundEffect.soundSource)
			{
				_currentlyLooping.erase(_currentlyLooping.begin() + i);
				break;
			}
		}

		soundEffect.isLooping = false;
	}

	void SoundManager::StopAllLoops()
	{
		if (!_isSetup)
			Setup();
	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="soundEffect"></param>
	/// <param name="stopPrevious">If true, the previous iteration of this sound effect will be stopped</param>
	/// <param name="looping"></param>
	/// <param name="needToCreateAPointer">If true, the play2D will assign a real pointer to soundEffect.sound. Useful, but wasteful</param>
	void SoundManager::PlaySoundEffect(SoundEffect &soundEffect, bool stopPrevious, bool looping, bool needToCreateAPointer)
	{
		if(!_isSetup)
			Setup();

		if (soundEffect.soundSource==nullptr) {
			soundEffect.soundSource = _engine->addSoundSourceFromFile(soundEffect.filepath.c_str());
			soundEffect.soundSource->setDefaultVolume(soundEffect.volume);
		}

		if (!stopPrevious && _engine->isCurrentlyPlaying(soundEffect.soundSource)) return;

		if (stopPrevious)
		{
			_engine->stopAllSoundsOfSoundSource(soundEffect.soundSource);
		}

		soundEffect.sound=_engine->play2D(soundEffect.soundSource,looping,false,false, needToCreateAPointer);
	}

	void SoundManager::Setup()
	{
		if(_isSetup)
			return;

		_engine = createIrrKlangDevice();

		_isSetup = true;
	}	

#pragma endregion
	irrklang::ISoundEngine* SoundManager::_engine;
	bool SoundManager::_isSetup = false;

	SoundEffect SoundManager::_clickSound = SoundEffect("res/sounds/click.wav");
	SoundEffect SoundManager::_rotateSound = SoundEffect("res/sounds/rotatingObjectLoop.wav");
	SoundEffect SoundManager::_nextLevelSound = SoundEffect("res/sounds/nextLevel2.wav");
	SoundEffect SoundManager::_laserSound = SoundEffect("res/sounds/laserLoop.wav",0.02f);
	const float SoundManager::_laserPitchStart = 0.8f;
	const float SoundManager::_laserPitchIncrement = 0.1f;
	const int SoundManager::_maxNbrOfLaserPitchShift = 10;
	
	std::vector<SoundEffect> SoundManager::_currentlyLooping= std::vector<SoundEffect>();

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

		if(numberOfCollisions >= _maxNbrOfLaserPitchShift)
			numberOfCollisions = _maxNbrOfLaserPitchShift;

		StartLoop(_laserSound,true);
		_laserSound.sound->setPlaybackSpeed(_laserPitchStart + numberOfCollisions * _laserPitchIncrement);
	}
}