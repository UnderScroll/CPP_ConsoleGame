#pragma once
#include <windows.h>

class Console {
public:
	static const unsigned int WIDTH = 2000*2;
	static const unsigned int HEIGHT = 80;

	static Console& GetInstance() {
		static Console S;
		return S;
	}

private:
	const HANDLE handle = (HANDLE)GetStdHandle(STD_OUTPUT_HANDLE);
	
	LONG_PTR SetConsoleWindowStyle(INT n_index, LONG_PTR new_style);

	COORD dwBufferCoord = { 0, 0 };
	SMALL_RECT rcRegion = { 0, 0, WIDTH - 1, HEIGHT - 1 };
	COORD dwBufferSize = { WIDTH, HEIGHT };
	CHAR_INFO buffer[HEIGHT][WIDTH];

public:
	void Setup();
	void Display();
	void Clear();	
	
	CHAR_INFO _virtual_buffer[WIDTH / 2][HEIGHT];
};