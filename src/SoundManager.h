#pragma once
#include <vector>
#include <string>

namespace core {
	class SoundManager
	{
	public:
		static void StartLoop(std::string filename);
		static void StopLoop(std::string filename);
		static void StopAllLoops();

		static void PlayAudioFile(std::string filename, float volume=1);

		static void PlayClickSound();
	private:
		static const std::string _clickSound;
		static std::vector<std::string> _currentLoops;
	};
}

