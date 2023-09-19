#pragma once
#include <windows.h>

class Console {
public:
	static const unsigned int WIDTH = 100;
	static const unsigned int HEIGHT = 100;
	COORD dwBufferCoord = { 0, 0 };
	SMALL_RECT rcRegion = { 0, 0, WIDTH - 1, HEIGHT- 1 };
	COORD dwBufferSize = {WIDTH, HEIGHT};
	
	void setup();
	void draw();

private:
	const HANDLE handle = (HANDLE)GetStdHandle(STD_OUTPUT_HANDLE);


	CHAR_INFO buffer[WIDTH][HEIGHT];
	

	void displayBuffer();
};