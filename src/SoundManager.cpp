#include "SoundManager.h"

#include <Windows.h>
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

	void SoundManager::StartLoop(std::string filename)
	{
	}
	void SoundManager::StopLoop(std::string filename)
	{
	}
	void SoundManager::StopAllLoops()
	{
	}

	void SoundManager::PlayAudioFile(std::string filename, float volume)
	{
		LPCWSTR convertedFilename= ConvertToLPWSTR(filename.c_str());
		PlaySound(convertedFilename, NULL, SND_FILENAME | SND_ASYNC);
	}
#pragma endregion

	const std::string SoundManager::_clickSound = "../res/sounds/BlastOfWind.wav";

	void SoundManager::PlayClickSound()
	{
		PlayAudioFile(_clickSound);
	}
}