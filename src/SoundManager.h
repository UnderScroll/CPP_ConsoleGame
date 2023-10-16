#pragma once
#include <vector>
#include <string>

namespace core {
	struct SoundEffect {
		std::string filepath;
		SoundEffect(std::string filepath) : filepath(filepath){};
		SoundEffect() : filepath(""){};

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

		static void PlaySoundEffect(SoundEffect soundEffect, bool stopPrevious = true);

		static void PlayClickSound();

		static void PlayRotateSound();

		static void PlayNextLevelSound();

		static void PlayLaserSound(int numberOfCollisions);
	private:
		static const SoundEffect _clickSound;
		static const SoundEffect _rotateSound;
		static const SoundEffect _nextLevelSound;
		static const std::vector<SoundEffect> _laserSounds;

		//Because we use "PlaySound" to loop sound effects, only one sound effect can be looped at a time
		static SoundEffect _currentLoop;
	};
}

