#pragma once
#include <vector>
#include <string>
#include <ik_ISoundEngine.h>

namespace core {
	struct SoundEffect {
		std::string filepath;
		float volume;
		SoundEffect(std::string filepath, float volume=1) : filepath(filepath), volume(volume){};
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
		static void StartLoop(SoundEffect soundEffect);
		static void StopLoop(SoundEffect soundEffect);
		static void StopAllLoops();

		static void PlaySoundEffect(SoundEffect soundEffect, bool allowOverlap=true);

		static void PlayClickSound();

		static void PlayRotateSound();

		static void PlayNextLevelSound();

		static void PlayLaserSound(int numberOfCollisions);

	private:
		static const SoundEffect _clickSound;
		static const SoundEffect _rotateSound;
		static const SoundEffect _nextLevelSound;
		static const std::vector<SoundEffect> _laserSounds;

		static irrklang::ISoundEngine* _engine;

		static bool _isInitialized;
		static void Initialize();
	};
}

