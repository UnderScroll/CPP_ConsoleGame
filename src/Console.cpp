#include "Console.h"

#include <iostream>
#include "Application.h"

Console Console::instance = Console();

void InitConsoleStyle(const HANDLE& handle) {
	SetLastError(NO_ERROR);

	CONSOLE_FONT_INFOEX cfi = { sizeof(cfi), 0, {0, 6} };
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);

	SMALL_RECT rect = { 0, 0, TRUE_WIDTH - 1, TRUE_HEIGHT - 1 };

	//Get console window handle
	HWND hwnd_console = GetConsoleWindow();

	//Get cursor info
	CONSOLE_CURSOR_INFO  cursorInfo;
	GetConsoleCursorInfo(handle, &cursorInfo);

	//Set cursor visibility
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(handle, &cursorInfo);

	//Set window Style
	SetWindowLongPtrA(hwnd_console, GWL_STYLE, WS_CAPTION | WS_SYSMENU);

	SetConsoleScreenBufferSize(handle, { TRUE_WIDTH, TRUE_HEIGHT });

	//Set window position
	SetWindowPos(hwnd_console, 0, 0, 0, 0, 0, SWP_HIDEWINDOW | SWP_NOSIZE);

	//Set window size
	SetConsoleWindowInfo(handle, TRUE, &rect);
	Console::SetConsoleSize(TRUE_WIDTH,TRUE_HEIGHT);

	ShowWindow(hwnd_console, SW_SHOW);
}

void Console::Setup() {
	InitConsoleStyle(handle);

	//Init buffer
	ReadConsoleOutput(handle, (CHAR_INFO*)buffer, dwBufferSize,
		dwBufferCoord, &rcRegion);
}

void Console::Display() {
	for (int x = 0;x < WIDTH;x++) {
		for (int y = 0;y < HEIGHT;y++) {
			buffer[y][x * 2] = _virtual_buffer[x][y];
			buffer[y][x * 2+1] = _virtual_buffer[x][y];
		}
	}

	WriteConsoleOutput(handle, (CHAR_INFO*)buffer, dwBufferSize,
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

//Snippets from the web
//
 BOOL Console::SetConsoleSize(int cols, int rows) {
	HWND hWnd;
	HANDLE hConOut;
	CONSOLE_FONT_INFO fi;
	CONSOLE_SCREEN_BUFFER_INFO bi;
	int w, h, bw, bh;
	RECT rect = {0, 0, 0, 0};
	COORD coord = {0, 0};
	hWnd = GetConsoleWindow();
	if (hWnd) {
		hConOut = GetStdHandle(STD_OUTPUT_HANDLE);
		if (hConOut && hConOut != (HANDLE)-1) {
			if (GetCurrentConsoleFont(hConOut, FALSE, &fi)) {
				if (GetClientRect(hWnd, &rect)) {
					w = rect.right-rect.left;
					h = rect.bottom-rect.top;
					if (GetWindowRect(hWnd, &rect)) {
						bw = rect.right-rect.left-w;
						bh = rect.bottom-rect.top-h;
						if (GetConsoleScreenBufferInfo(hConOut, &bi)) {
							coord.X = bi.dwSize.X;
							coord.Y = bi.dwSize.Y;
							if (coord.X < cols || coord.Y < rows) {
								if (coord.X < cols) {
									coord.X = cols;
								}
								if (coord.Y < rows) {
									coord.Y = rows;
								}
								if (!SetConsoleScreenBufferSize(hConOut, coord)) {
									return FALSE;
								}
							}
							return SetWindowPos(hWnd, NULL, rect.left, rect.top, cols*fi.dwFontSize.X+bw, rows*fi.dwFontSize.Y+bh, SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);
						}
					}
				}
			}
		}
	}
	return FALSE;
}