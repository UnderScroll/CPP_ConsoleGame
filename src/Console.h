#pragma once
#include <windows.h>

class Console {
private:
	const HANDLE handle = (HANDLE)GetStdHandle(STD_OUTPUT_HANDLE);
	
	LONG_PTR SetConsoleWindowStyle(INT n_index, LONG_PTR new_style);

	COORD dwBufferCoord = { 0, 0 };
	SMALL_RECT rcRegion = { 0, 0, WIDTH - 1, HEIGHT - 1 };
	COORD dwBufferSize = { WIDTH, HEIGHT };
public:
	void Setup();
	void Display();
	void Clear();

	static const unsigned int WIDTH = 100 * 2;
	static const unsigned int HEIGHT = 80;

	CHAR_INFO buffer[HEIGHT][WIDTH];
};