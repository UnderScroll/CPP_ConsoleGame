#pragma once
#include <windows.h>

#define WIDTH 328
#define HEIGHT 124
#define TRUE_WIDTH WIDTH * 2
#define TRUE_HEIGHT HEIGHT

namespace core {

class Console {
public:
	void Setup();
	void Display();
	void Clear();
	
	static BOOL SetConsoleSize(const HWND& windowHandle, const HANDLE& stdOutHandle, int cols, int rows);

	CHAR_INFO buffer[TRUE_HEIGHT][TRUE_WIDTH];

	static Console& GetInstance() { return instance; }

	CHAR_INFO _virtual_buffer[WIDTH][HEIGHT];

	static const HANDLE stdOutHandle;
	static const HWND windowHandle;
private:

	COORD dwBufferCoord = { 0, 0 };
	SMALL_RECT rcRegion = { 0, 0, TRUE_WIDTH - 1, TRUE_HEIGHT - 1 };
	COORD dwBufferSize = { TRUE_WIDTH, TRUE_HEIGHT };

	void InitConsoleStyle(const HANDLE& handle);

	static Console instance;
};

}

