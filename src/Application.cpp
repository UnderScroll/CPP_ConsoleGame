#include "Application.h"
#include <iostream>

bool Application::isOpen = true; //Init isOpen state
Console Application::cons = Console();

void Application::run() {
	std::cout << "[INFO] Starting application" << std::endl;
	
	setup();
	while (isOpen) {
		input();
		update();
		draw();
	}

	std::cout << "[INFO] Ending application" << std::endl;
}

void Application::setup() {
	std::cout << "[INFO] Setting up..." << std::endl;
	cons.setup();
}

void Application::input() {

}

void Application::update() {

}

void Application::draw() {
	cons.draw();
}