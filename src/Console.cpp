#include "Console.h"

#include <iostream>
#include "Application.h"

BOOL SetConsoleFontSize(const HANDLE& handle, COORD dwFontSize) {
	CONSOLE_FONT_INFOEX info{
		sizeof(CONSOLE_FONT_INFOEX)
	};
	
	if (!GetCurrentConsoleFontEx(handle, false, &info))
		return false;
	info.dwFontSize = dwFontSize;

	return SetCurrentConsoleFontEx(handle, false, &info);
}

LONG_PTR Console::SetConsoleWindowStyle(INT n_index, LONG_PTR new_style)
{
	SetLastError(NO_ERROR);

	HWND hwnd_console = GetConsoleWindow();
	LONG_PTR style_ptr = SetWindowLongPtr(hwnd_console, n_index, new_style);
	SetWindowPos(hwnd_console, 0, 0, 0, 0, 0, SWP_NOZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_DRAWFRAME);
	
	SetConsoleFontSize(handle, { 1, 5 });

	//show window after updating
	ShowWindow(hwnd_console, SW_SHOW);

	CONSOLE_CURSOR_INFO  cursorInfo;

	GetConsoleCursorInfo(handle, &cursorInfo);
	cursorInfo.bVisible = false; // set the cursor visibility
	SetConsoleCursorInfo(handle, &cursorInfo);


	return style_ptr;
}

void Console::Setup() {
	LONG_PTR new_style = WS_OVERLAPPEDWINDOW;
	SetConsoleWindowStyle(GWL_STYLE, new_style);

	ReadConsoleOutput(handle, (CHAR_INFO*)buffer, dwBufferSize,
		dwBufferCoord, &rcRegion);
}

void Console::Display() {
	for (int x = 0;x < WIDTH/2;x++) {
		for (int y = 0;y < HEIGHT;y++) {
			buffer[y][x * 2] = _virtual_buffer[x][y];
			buffer[y][x * 2+1] = _virtual_buffer[x][y];
			/*if (Console::GetInstance()._virtual_buffer[x][y].Char.UnicodeChar == ' ') continue;
			Application::GetInstance().ofstream << "BUFFER HAS NON NULL CHARACTER AT x " << x << " y" << y << " " << Console::GetInstance()._virtual_buffer[x][y].Char.UnicodeChar << std::endl;*/
		}
	}

	WriteConsoleOutput(handle, (CHAR_INFO*)buffer, dwBufferSize,
		dwBufferCoord, &rcRegion);
}

void Console::Clear() {
	for (size_t x = 0; x < WIDTH; ++x) {
		for (size_t y = 0; y < HEIGHT; ++y) {
			buffer[y][x].Char.UnicodeChar = ' ';
		}
	}
	for (size_t x = 0; x < WIDTH / 2; ++x) {
		for (size_t y = 0; y < HEIGHT; ++y) {
			_virtual_buffer[x][y].Char.UnicodeChar = ' ';
		}
	}
}