#pragma once
#include <windows.h>
#include "Drawable.h"

class Console {
private:
	const HANDLE handle = (HANDLE)GetStdHandle(STD_OUTPUT_HANDLE);
	
	LONG_PTR setConsoleWindowStyle(INT n_index, LONG_PTR new_style);
	void readConsoleOutput();
	void writeConsoleOutput();

	static const unsigned int WIDTH = 100;
	static const unsigned int HEIGHT = 100;
	COORD dwBufferCoord = { 0, 0 };
	SMALL_RECT rcRegion = { 0, 0, WIDTH - 1, HEIGHT - 1 };
	COORD dwBufferSize = { WIDTH, HEIGHT };

public:
	void setup();
	void display();

	CHAR_INFO buffer[WIDTH][HEIGHT];
};