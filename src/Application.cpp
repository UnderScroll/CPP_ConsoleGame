#include "Application.h"

#include <iostream>

#include "Character.h"

bool Application::isOpen = true; //Init isOpen state
Console Application::console = Console();

void Application::run() {
	setup();
	while (isOpen) {
		input();
		update();
		draw();
	}
}

void Application::setup() {
	console.setup();
}

void Application::input() {
}

void Application::update() {
	
}

void Application::draw() {
	Character character = Character();
	character.Draw(console);
	console.display();
}