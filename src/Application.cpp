#include "Application.h"

#include <iostream>
#include <thread>

Application Application::instance = Application();

void Application::InstanceRun() {
	Setup();
	while (isOpen) {
		auto end = std::chrono::steady_clock::now() + std::chrono::milliseconds(1);
		
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
}

void Application::Update() {
	character.pos.x = ++character.pos.x % console.WIDTH;
}

void Application::Draw() {
	console.Clear();

	character.Draw(console);

	console.Display();
}