#include "Application.h"

#include <iostream>

Application Application::instance = Application();

void Application::InstanceRun() {
	Setup();
	while (isOpen) {
		Input();
		Update();
		Draw();
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