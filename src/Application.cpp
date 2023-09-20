#include "Application.h"

#include <iostream>
#include <thread>

#define MIN_FRAMETIME_MS 1000

Application Application::instance = Application();

void Application::InstanceRun() {
	Setup();
	while (isOpen) {
		auto end = std::chrono::steady_clock::now() + std::chrono::milliseconds(MIN_FRAMETIME_MS);
		
		Input();
		Update();
		Draw();

		std::this_thread::sleep_until(end);
	}
}

void Application::Setup() {
	console.Setup();
	isOpen = true;

	character = Character();
}

void Application::Input() {
	if (GetKeyState(VK_RETURN) & 0x8000) {
		std::cout << "HELLO" << std::endl;
	}
}

void Application::Update() {
	character._pos._x++;
	character._pos._x = (int)character._pos._x % (Console::WIDTH / 2);
	character._pos._y++;
	character._pos._y = (int)character._pos._y % Console::HEIGHT;
}

void Application::Draw() {
	console.Clear();

	character.Draw(console);

	console.Display();
}