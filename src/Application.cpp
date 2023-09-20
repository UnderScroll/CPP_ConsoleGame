#include "Application.h"

#include <iostream>
#include <thread>

#include "Vector2.h"
#include "PolygonObject.h"

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
	std::vector<Vector2> points;
	points.push_back(Vector2(+5.5, 5));
	points.push_back(Vector2(-25.7, -10));
	//points.push_back(Vector2(5.5, -5));
	polygon = PolygonObject(points, 0x0007);
	polygon._position = Vector2(30, 20);
}

void Application::Input() {
}

void Application::Update() {

}

void Application::Draw() {
	console.Clear();

	polygon.Draw();

	console.Display();
}