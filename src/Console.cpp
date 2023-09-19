#include "Console.h"

LONG_PTR Console::setConsoleWindowStyle(INT n_index, LONG_PTR new_style)
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

void Console::setup() {
	LONG_PTR new_style = WS_OVERLAPPEDWINDOW | WS_HSCROLL | WS_VSCROLL;
	setConsoleWindowStyle(GWL_STYLE, new_style);

	readConsoleOutput();
}

void Console::writeConsoleOutput() {
	WriteConsoleOutput(handle, (CHAR_INFO*)buffer, dwBufferSize,
		dwBufferCoord, &rcRegion);
}

void Console::readConsoleOutput() {
	ReadConsoleOutput(handle, (CHAR_INFO*)buffer, dwBufferSize,
		dwBufferCoord, &rcRegion);
}

void Console::display() {
	writeConsoleOutput();
}