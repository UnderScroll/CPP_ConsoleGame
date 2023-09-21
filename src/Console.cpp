#include "Console.h"

#include <iostream>

Console Console::instance = Console();
const HANDLE Console::stdOutHandle = (HANDLE)GetStdHandle(STD_OUTPUT_HANDLE);
const HWND Console::windowHandle = GetConsoleWindow();

void Console::InitConsoleStyle(const HANDLE& handle) {
	SetLastError(NO_ERROR);

	CONSOLE_FONT_INFOEX cfi = { sizeof(cfi), 0, {0, 6} };
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);

	SMALL_RECT rect = { 0, 0, WIDTH - 1, HEIGHT- 1 };

	//Get cursor info
	CONSOLE_CURSOR_INFO  cursorInfo;
	GetConsoleCursorInfo(handle, &cursorInfo);

	//Set cursor visibility
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(handle, &cursorInfo);

	//Set window Style
	SetWindowLongPtrA(windowHandle, GWL_STYLE, WS_CAPTION | WS_SYSMENU);
	
	SetConsoleScreenBufferSize(handle, { WIDTH, HEIGHT });

	//Set window position
	SetWindowPos(windowHandle, 0, 0, 0, 0, 0, SWP_HIDEWINDOW | SWP_NOSIZE);

	//Remove Quick Edit Mode
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	DWORD prev_mode;
	GetConsoleMode(hInput, &prev_mode);
	SetConsoleMode(hInput, ENABLE_EXTENDED_FLAGS | (prev_mode & ~ENABLE_QUICK_EDIT_MODE));

	//Set window size
	SetConsoleWindowInfo(handle, TRUE, &rect);

	ShowWindow(windowHandle, SW_SHOW);
}

void Console::Setup() {
	InitConsoleStyle(stdOutHandle);

	//Init buffer
	ReadConsoleOutput(stdOutHandle, (CHAR_INFO*)buffer, dwBufferSize,
		dwBufferCoord, &rcRegion);
}

void Console::Display() {
	for (int x = 0;x < WIDTH;x++) {
		for (int y = 0;y < HEIGHT;y++) {
			buffer[y][x * 2] = _virtual_buffer[x][y];
			buffer[y][x * 2+1] = _virtual_buffer[x][y];
		}
	}

	WriteConsoleOutput(stdOutHandle, (CHAR_INFO*)buffer, dwBufferSize,
		dwBufferCoord, &rcRegion);
}

void Console::Clear() {
	for (size_t x = 0; x < TRUE_WIDTH; ++x) {
		for (size_t y = 0; y < TRUE_HEIGHT; ++y) {
			buffer[y][x].Char.UnicodeChar = ' ';
		}
	}
	for (size_t x = 0; x < WIDTH / 2; ++x) {
		for (size_t y = 0; y < HEIGHT; ++y) {
			_virtual_buffer[x][y].Char.UnicodeChar = ' ';
		}
	}
}