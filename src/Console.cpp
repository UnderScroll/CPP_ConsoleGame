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
	_virtual_buffer[4][10].Char.UnicodeChar = 0x2588;
	_virtual_buffer[4][10].Attributes = 0x0001;
	_virtual_buffer[5][10].Char.UnicodeChar = 0x2588;
	_virtual_buffer[5][10].Attributes = 0x0001;
	_virtual_buffer[6][10].Char.UnicodeChar = 0x2588;
	_virtual_buffer[6][10].Attributes = 0x0001;
	_virtual_buffer[7][11].Char.UnicodeChar = 0x2588;
	_virtual_buffer[7][11].Attributes = 0x0001;
	_virtual_buffer[8][11].Char.UnicodeChar = 0x2588;
	_virtual_buffer[8][11].Attributes = 0x0001;
	_virtual_buffer[9][12].Char.UnicodeChar = 0x2588;
	_virtual_buffer[9][12].Attributes = 0x0001;
	_virtual_buffer[10][12].Char.UnicodeChar = 0x2588;
	_virtual_buffer[10][12].Attributes = 0x0001;
	_virtual_buffer[11][13].Char.UnicodeChar = 0x2588;
	_virtual_buffer[11][13].Attributes = 0x0001;
	_virtual_buffer[12][13].Char.UnicodeChar = 0x2588;
	_virtual_buffer[12][13].Attributes = 0x0001;
	_virtual_buffer[13][14].Char.UnicodeChar = 0x2588;
	_virtual_buffer[13][14].Attributes = 0x0001;
	_virtual_buffer[14][14].Char.UnicodeChar = 0x2588;
	_virtual_buffer[14][14].Attributes = 0x0001;
	_virtual_buffer[15][15].Char.UnicodeChar = 0x2588;
	_virtual_buffer[15][15].Attributes = 0x0001;
	_virtual_buffer[16][15].Char.UnicodeChar = 0x2588;
	_virtual_buffer[16][15].Attributes = 0x0001;
	_virtual_buffer[17][16].Char.UnicodeChar = 0x2588;
	_virtual_buffer[17][16].Attributes = 0x0001;
	_virtual_buffer[18][16].Char.UnicodeChar = 0x2588;
	_virtual_buffer[18][16].Attributes = 0x0001;
	_virtual_buffer[19][17].Char.UnicodeChar = 0x2588;
	_virtual_buffer[19][17].Attributes = 0x0001;
	_virtual_buffer[20][17].Char.UnicodeChar = 0x2588;
	_virtual_buffer[20][17].Attributes = 0x0001;
	_virtual_buffer[21][18].Char.UnicodeChar = 0x2588;
	_virtual_buffer[21][18].Attributes = 0x0001;
	_virtual_buffer[22][18].Char.UnicodeChar = 0x2588;
	_virtual_buffer[22][18].Attributes = 0x0001;
	_virtual_buffer[23][19].Char.UnicodeChar = 0x2588;
	_virtual_buffer[23][19].Attributes = 0x0001;
	_virtual_buffer[24][19].Char.UnicodeChar = 0x2588;
	_virtual_buffer[24][19].Attributes = 0x0001;
	_virtual_buffer[25][20].Char.UnicodeChar = 0x2588;
	_virtual_buffer[25][20].Attributes = 0x0001;
	_virtual_buffer[26][20].Char.UnicodeChar = 0x2588;
	_virtual_buffer[26][20].Attributes = 0x0001;
	_virtual_buffer[27][21].Char.UnicodeChar = 0x2588;
	_virtual_buffer[27][21].Attributes = 0x0001;
	_virtual_buffer[28][21].Char.UnicodeChar = 0x2588;
	_virtual_buffer[28][21].Attributes = 0x0001;
	_virtual_buffer[29][22].Char.UnicodeChar = 0x2588;
	_virtual_buffer[29][22].Attributes = 0x0001;
	_virtual_buffer[30][22].Char.UnicodeChar = 0x2588;
	_virtual_buffer[30][22].Attributes = 0x0001;
	_virtual_buffer[31][22].Char.UnicodeChar = 0x2588;
	_virtual_buffer[31][22].Attributes = 0x0001;
	_virtual_buffer[32][23].Char.UnicodeChar = 0x2588;
	_virtual_buffer[32][23].Attributes = 0x0001;
	_virtual_buffer[33][23].Char.UnicodeChar = 0x2588;
	_virtual_buffer[33][23].Attributes = 0x0001;
	_virtual_buffer[34][24].Char.UnicodeChar = 0x2588;
	_virtual_buffer[34][24].Attributes = 0x0001;
	_virtual_buffer[35][24].Char.UnicodeChar = 0x2588;
	_virtual_buffer[35][24].Attributes = 0x0001;

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