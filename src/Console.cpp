#include "Console.h"

#include <iostream>

namespace core {

Console Console::_instance = Console();
const HANDLE Console::stdOutHandle = (HANDLE)GetStdHandle(STD_OUTPUT_HANDLE);
const HWND Console::windowHandle = GetConsoleWindow();

void Console::InitConsoleStyle(const HANDLE& handle) {
	SetLastError(NO_ERROR);

	CONSOLE_FONT_INFOEX cfi = { sizeof(cfi), 0, {0, 6} };
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);

	SMALL_RECT rect = { 0, 0, static_cast<short>(WIDTH - 1), static_cast<short>(HEIGHT - 1 )};

	//Get cursor info
	CONSOLE_CURSOR_INFO  cursorInfo;
	GetConsoleCursorInfo(handle, &cursorInfo);

	//Set cursor visibility
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(handle, &cursorInfo);

	//Set window Style
	SetWindowLongPtrA(windowHandle, GWL_STYLE, WS_CAPTION | WS_SYSMENU);

	SetConsoleTitle(L"Lasciier Attraction");

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
	//Console::SetConsoleSize(windowHandle, stdOutHandle, WIDTH, HEIGHT);

	ShowWindow(windowHandle, SW_SHOW);
}

void Console::Setup() {
	InitConsoleStyle(stdOutHandle);

	//Init buffer
	ReadConsoleOutput(stdOutHandle, (CHAR_INFO*)_buffer, _dwBufferSize,
		_dwBufferCoord, &_rcRegion);
}

void Console::Display() {
	for (int x = 0; x < WIDTH; x++) {
		for (int y = 0; y < HEIGHT; y++) {
			_buffer[y][x * 2].Char.UnicodeChar = _virtual_buffer[x][y].charToUse;
			if (_virtual_buffer[x][y].backgroundColor!=0) {
				_virtual_buffer[x][y].backgroundColor;
			}
			_buffer[y][x * 2].Attributes = _virtual_buffer[x][y].color+(_virtual_buffer[x][y].backgroundColor << 4);
			_buffer[y][x * 2 + 1] = _buffer[y][x * 2];
		}
	}

	WriteConsoleOutput(stdOutHandle, (CHAR_INFO*)_buffer, _dwBufferSize,
		_dwBufferCoord, &_rcRegion);
}

void Console::Clear() {
	for (size_t x = 0; x < TRUE_WIDTH; ++x) {
		for (size_t y = 0; y < TRUE_HEIGHT; ++y) {
			_buffer[y][x].Char.UnicodeChar = ' ';
		}
	}
	for (size_t x = 0; x < WIDTH / 2; ++x) {
		for (size_t y = 0; y < HEIGHT; ++y) {
			_virtual_buffer[x][y].charToUse = ' ';
			_virtual_buffer[x][y].color = 0x0007;
			_virtual_buffer[x][y].backgroundColor = 0x0000;
		}
	}
}

//Snippets from the web
//
//BOOL Console::SetConsoleSize(const HWND& windowHandle, const HANDLE& stdOutHandle, int cols, int rows) {
//	CONSOLE_FONT_INFO fi;
//	CONSOLE_SCREEN_BUFFER_INFO bi;
//
//	int w, h, bw, bh;
//	RECT rect = { 0, 0, 0, 0 };
//	COORD coord = { 0, 0 };
//
//	Get context
//	if (!GetCurrentConsoleFont(stdOutHandle, FALSE, &fi) ||
//		!GetClientRect(windowHandle, &rect) ||
//		!GetWindowRect(windowHandle, &rect) ||
//		!GetConsoleScreenBufferInfo(stdOutHandle, &bi))
//		return false;
//
//	w = rect.right - rect.left;
//	h = rect.bottom - rect.top;
//
//	bw = rect.right - rect.left - w;
//	bh = rect.bottom - rect.top - h;
//
//	coord.X = bi.dwSize.X;
//	coord.Y = bi.dwSize.Y;
//	if (coord.X < cols || coord.Y < rows) {
//		if (coord.X < cols) {
//			coord.X = cols;
//		}
//		if (coord.Y < rows) {
//			coord.Y = rows;
//		}
//		if (!SetConsoleScreenBufferSize(stdOutHandle, coord)) {
//			return false;
//		}
//	}
//
//	return SetWindowPos(windowHandle, NULL, rect.left, rect.top, cols * fi.dwFontSize.X + bw, rows * fi.dwFontSize.Y + bh, SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);
//}

}