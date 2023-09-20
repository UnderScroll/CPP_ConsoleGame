#include "Console.h"

LONG_PTR Console::SetConsoleWindowStyle(INT n_index, LONG_PTR new_style)
{
	SetLastError(NO_ERROR);

	HWND hwnd_console = GetConsoleWindow();
	LONG_PTR style_ptr = SetWindowLongPtr(hwnd_console, n_index, new_style);
	SetWindowPos(hwnd_console, 0, 0, 0, 0, 0, SWP_NOZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_DRAWFRAME);

	//show window after updating
	ShowWindow(hwnd_console, SW_SHOW);

	CONSOLE_CURSOR_INFO  cursorInfo;

	GetConsoleCursorInfo(handle, &cursorInfo);
	cursorInfo.bVisible = false; // set the cursor visibility
	SetConsoleCursorInfo(handle, &cursorInfo);

	return style_ptr;
}

void Console::Setup() {
	LONG_PTR new_style = WS_OVERLAPPEDWINDOW | WS_HSCROLL | WS_VSCROLL;
	SetConsoleWindowStyle(GWL_STYLE, new_style);

	ReadConsoleOutput(handle, (CHAR_INFO*)buffer, dwBufferSize,
		dwBufferCoord, &rcRegion);
}

void Console::Display() {
	WriteConsoleOutput(handle, (CHAR_INFO*)buffer, dwBufferSize,
		dwBufferCoord, &rcRegion);
}

void Console::Clear() {
	for (size_t x = 0; x < WIDTH; ++x) {
		for (size_t y = 0; y < HEIGHT; ++y) {
			buffer[y][x].Char.UnicodeChar = ' ';
		}
	}
}