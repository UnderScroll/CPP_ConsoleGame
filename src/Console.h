#pragma once
#include <windows.h>

#define WIDTH 328
#define HEIGHT 124
#define TRUE_WIDTH WIDTH * 2
#define TRUE_HEIGHT HEIGHT

namespace core {

struct Pixel {
	char charToUse;
	WORD color;
	WORD backgroundColor;
};
class Console {
public:
	void Setup();
	void Display();
	void Clear();
	
	//static BOOL SetConsoleSize(const HWND& windowHandle, const HANDLE& stdOutHandle, int cols, int rows);

	CHAR_INFO _buffer[TRUE_HEIGHT][TRUE_WIDTH];

	static Console& GetInstance() { return _instance; }

	Pixel _virtual_buffer[WIDTH][HEIGHT];

	static const HANDLE stdOutHandle;
	static const HWND windowHandle;
private:

	COORD _dwBufferCoord = { 0, 0 };
	SMALL_RECT _rcRegion = { 0, 0, TRUE_WIDTH - 1, TRUE_HEIGHT - 1 };
	COORD _dwBufferSize = { TRUE_WIDTH, TRUE_HEIGHT };

	void InitConsoleStyle(const HANDLE& handle);

	static Console _instance;
};

}

