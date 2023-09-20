#include "Application.h"

#include <iostream>
#include <thread>

#define MIN_FRAMETIME_MS 10

Application Application::instance = Application();

Character chars[200];

void Application::InstanceRun() {
	Setup();
	while (isOpen) {
		auto waitTime = std::chrono::steady_clock::now() + std::chrono::milliseconds(MIN_FRAMETIME_MS);
		auto framestart = std::chrono::steady_clock::now();
		
		Input();
		Update();
		Draw();

		
		std::this_thread::sleep_until(waitTime);
		frameCount++;

		auto frameEnd = std::chrono::steady_clock::now();
		ofstream << "[INFO] Frame : " << frameCount << " - " << "frameTime : " << std::chrono::duration_cast<std::chrono::milliseconds>(frameEnd - framestart).count() << "ms" << std::endl;
	}

	ofstream.close();
}

void Application::Setup() {
	console.Setup();
	isOpen = true;

	character = Character();

	for (Character& c : chars) {
		c._pos._x = rand() % 200;
		c._pos._y = rand() % 80;
	}
}

void Application::Input() {
	/*if (GetKeyState(VK_RETURN) & 0x8000) {
		ofstream << "[INFO] - " << frameCount << " - VK_RETURN" << std::endl;
	}
	if (GetKeyState(VK_ESCAPE) & 0x8000) {
		ofstream << "[INFO] - " << frameCount << " - VK_ESCAPE" << std::endl;
		isOpen = false;
	}*/
	BYTE keyboardState[256];
	if (!GetKeyboardState(keyboardState)) {
		ofstream << "[INFO] - " << frameCount << " - Keyboard : " << keyboardState << std::endl;
	};
	
}

void Application::Update() {
	character._pos._x++;
	character._pos._x = (int)character._pos._x % (Console::WIDTH / 2);
	character._pos._y++;
	character._pos._y = (int)character._pos._y % Console::HEIGHT;

	for (Character& c : chars) {
		c._pos._x++;
		c._pos._x = (int)c._pos._x % (Console::WIDTH / 2);
		c._pos._y++;
		c._pos._y = (int)c._pos._y % Console::HEIGHT;
	}
}

void Application::Draw() {
	console.Clear();

	character.Draw(console);
	for (Character& c : chars) {
		c.Draw(console);
	}

	console.Display();
}