#pragma once
#include <vector>
#include <string>
#include <ik_ISoundEngine.h>
#include <map>

namespace core {
	struct SoundEffect {
		std::string filepath;
		float volume;
		irrklang::ISoundSource *soundSource=nullptr;
		bool isLooping = false;
		irrklang::ISound *sound = nullptr;

		SoundEffect(std::string filepath, float volume=1) : filepath(filepath), volume(volume)
		{
		};
		SoundEffect() : SoundEffect(""){};

		bool operator==(const SoundEffect& other) const {
			return filepath == other.filepath;
		}
		bool operator!=(const SoundEffect& other) const {
			return !(*this == other);
		}
	};



	class SoundManager
	{
	public:
		static void StartLoop(SoundEffect &soundEffect, bool needToCreateAPointer = false);
		static void StopLoop(SoundEffect &soundEffect, bool removeFromVector=true);
		static void StopAllLoops();

		static void PlaySoundEffect(SoundEffect& soundEffect, bool stopPrevious = true, bool looping = false, bool needToCreateAPointer=false);

		static void PlayClickSound();

		static void PlayRotateSound();

		static void PlayNextLevelSound();

		static void PlayPoweringUpSound(float stage);

		static void PlayLaserSound(int numberOfCollisions);

		static void Setup();

	private:
		static SoundEffect _clickSound;
		static SoundEffect _rotateSound;
		static SoundEffect _nextLevelSound;
		static SoundEffect _laserSound;
		static const float _laserPitchStart;
		static const float _laserPitchEnd;
		static const int _maxNbrOfLaserPitchShift;

		static std::vector<SoundEffect*> _currentlyLooping;
		static irrklang::ISoundEngine* _engine;

		static bool _isSetup;
	};
}

