#include "Console.h"

LONG_PTR setConsoleWindowStyle(INT n_index, LONG_PTR new_style)
{
	/*The function does not clear the last error information. if last value was zero.*/
	SetLastError(NO_ERROR);

	HWND hwnd_console = GetConsoleWindow();
	LONG_PTR style_ptr = SetWindowLongPtr(hwnd_console, n_index, new_style);
	SetWindowPos(hwnd_console, 0, 0, 0, 0, 0, SWP_NOZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_DRAWFRAME);

	//show window after updating
	ShowWindow(hwnd_console, SW_SHOW);

	return style_ptr;
}

void Console::setup() {
	LONG_PTR new_style = WS_OVERLAPPEDWINDOW | WS_HSCROLL | WS_VSCROLL;
	setConsoleWindowStyle(GWL_STYLE, new_style);
}


void Console::displayBuffer() {
	ReadConsoleOutput(handle, (CHAR_INFO*)buffer, dwBufferSize,
		dwBufferCoord, &rcRegion);

	WriteConsoleOutput(handle, (CHAR_INFO*)buffer, dwBufferSize,
		dwBufferCoord, &rcRegion);
}

void Console::draw() {
	buffer[5][10].Char.AsciiChar = 'H';
	buffer[5][10].Attributes = 0x0E;
	buffer[5][11].Char.AsciiChar = 'i';
	buffer[5][11].Attributes = 0x0B;
	buffer[5][12].Char.AsciiChar = '!';
	buffer[5][12].Attributes = 0x0A;

	displayBuffer();
}