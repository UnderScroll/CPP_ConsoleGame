#pragma once
#include <vector>
#include <string>

namespace core {
	struct SoundEffect {
		std::string filepath;
		float volume;
		SoundEffect(std::string filepath, float volume = 1) : filepath(filepath), volume(volume) {};
		SoundEffect() : SoundEffect("", 1) {};

		bool operator==(const SoundEffect& other) const {
			return filepath == other.filepath && volume==other.volume;
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

		static void PlaySoundEffect(SoundEffect soundEffect, bool stopPrevious=true);

		static void PlayClickSound();

		static void PlayRotateSound();

		static void PlayNextLevelSound();
	private:
		static const SoundEffect _clickSound;
		static const SoundEffect _rotateSound;
		static const SoundEffect _nextLevelSound;
		static const SoundEffect _laserSound;
		static int _numberOfLasers;
		static const double _laserPitches[];
		//Because we use "PlaySound" to loop sound effects, only one sound effect can be looped at a time
		static SoundEffect _currentLoop;
	};
}

