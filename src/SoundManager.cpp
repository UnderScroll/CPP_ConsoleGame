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
		_currentlyLooping.push_back(&soundEffect);
	}

	void SoundManager::StopLoop(SoundEffect &soundEffect, bool removeFromVector)
	{
		if (!_isSetup)
			Setup();

		if (!soundEffect.isLooping) {
			return;
		}

		_engine->stopAllSoundsOfSoundSource(soundEffect.soundSource);

		soundEffect.isLooping = false;

		if(!removeFromVector)
			return;

		//Remove the sound source from the _currentlyLooping ones
		for (int i = 0; i < _currentlyLooping.size(); i++)
		{
			if (_currentlyLooping[i]->soundSource == soundEffect.soundSource)
			{
				_currentlyLooping.erase(_currentlyLooping.begin() + i);
				break;
			}
		}

	}

	void SoundManager::StopAllLoops()
	{
		if (!_isSetup)
			Setup();

		for (int i = 0; i < _currentlyLooping.size(); i++)
		{
			StopLoop(*_currentlyLooping[i], false);
		}
		_currentlyLooping.clear();
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

		if (soundEffect.sound != nullptr) {
			soundEffect.sound->drop(); //Avoid memory leaks
			//We drop it now because dropping it at another time (when you unload a level) could mess up the code, because not every update is over when a new level is loaded, 
			//So an object could still ask to change the pitch of a dropped sound
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
	SoundEffect SoundManager::_laserSound = SoundEffect("res/sounds/laserLoop.wav",0.6f);
	const float SoundManager::_laserPitchStart = 0.5f;
	const float SoundManager::_laserPitchEnd = 3;
	const int SoundManager::_maxNbrOfLaserPitchShift = 10;
	
	std::vector<SoundEffect*> SoundManager::_currentlyLooping= std::vector<SoundEffect*>();

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

	void SoundManager::PlayPoweringUpSound(float stage) {
		PlaySoundEffect(_laserSound, false, false, true);
		
		PlaySoundEffect(_laserSound,false,true);
		_laserSound.sound->setPlaybackSpeed(_laserPitchStart + stage * (_laserPitchEnd-_laserPitchStart));
	}

	//Never called because it was too annoying
	void SoundManager::PlayLaserSound(int numberOfCollisions)
	{
		if(numberOfCollisions < 0)
			numberOfCollisions = 0;

		if(numberOfCollisions >= _maxNbrOfLaserPitchShift)
			numberOfCollisions = _maxNbrOfLaserPitchShift;

		StartLoop(_laserSound,true);
		_laserSound.sound->setPlaybackSpeed(_laserPitchStart + float(numberOfCollisions/ _maxNbrOfLaserPitchShift) * (_laserPitchEnd- _laserPitchStart));
	}
}