#pragma once
#include <windows.h>

#define WIDTH 328
#define HEIGHT 124
#define TRUE_WIDTH WIDTH * 2
#define TRUE_HEIGHT HEIGHT

class Console {
public:
	void Setup();
	void Display();
	void Clear();
	
	static BOOL SetConsoleSize(int cols, int rows);

	CHAR_INFO buffer[TRUE_HEIGHT][TRUE_WIDTH];

	static Console& GetInstance() { return instance; }

	CHAR_INFO _virtual_buffer[WIDTH][HEIGHT];
private:
	const HANDLE handle = (HANDLE)GetStdHandle(STD_OUTPUT_HANDLE);

	COORD dwBufferCoord = { 0, 0 };
	SMALL_RECT rcRegion = { 0, 0, TRUE_WIDTH - 1, TRUE_HEIGHT - 1 };
	COORD dwBufferSize = { TRUE_WIDTH, TRUE_HEIGHT };

	static Console instance;
};