#include "Application.h"

#include <iostream>
#include <thread>

Application Application::instance = Application();

void Application::InstanceRun() {
	Setup();
	while (isOpen) {
		auto end = std::chrono::steady_clock::now() + std::chrono::milliseconds(10);
		
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
	character._pos._x = ++character._pos._x;
	if (character._pos._x >= console.WIDTH / 2) {
		character._pos._x = console.WIDTH - character._pos._x;
		character._pos._y = character._pos._y >= console.HEIGHT ? console.HEIGHT - character._pos._y : character._pos._y + 1;
	}
}

void Application::Draw() {
	console.Clear();

	character.Draw(console);

	console.Display();
}