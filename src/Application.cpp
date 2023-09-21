#include "Application.h"

#include <iostream>
#include <thread>

#include "Vector2.h"
#include "PolygonObject.h"
#define MIN_FRAMETIME_MS 10

Application Application::instance = Application();
std::ofstream Application::ofstream = std::ofstream("runtime.log");

Application::~Application() {
	ofstream.close();
}

void Application::InstanceRun() {
	Setup();
	while (isOpen) {
		auto waitTime = std::chrono::steady_clock::now() + std::chrono::milliseconds(MIN_FRAMETIME_MS);
		auto frameStart = std::chrono::steady_clock::now();
		
		Input();
		Update();
		Draw();

		std::this_thread::sleep_until(waitTime);
		frameCount++;

		auto frameEnd = std::chrono::steady_clock::now();
		ofstream << "[INFO] Frame : " << frameCount << " - " << "frameTime : " << std::chrono::duration_cast<std::chrono::milliseconds>(frameEnd - frameStart).count() << "ms" << std::endl;
	}
}

void Application::Setup() {
	console.Setup();
	isOpen = true;
	std::vector<Vector2> points;
	points.push_back(Vector2(+7.5, 12));
	points.push_back(Vector2(-25.7, -10));
	points.push_back(Vector2(5.5, -5));
	polygon = PolygonObject(points, 0x0007);
	polygon.MoveTo(Vector2(30, 30));
}

POINT Application::GetCursorPosition() {
	POINT cursorPosition;

	GetCursorPos(&cursorPosition);

	RECT rect;
	GetWindowRect(Console::windowHandle, &rect);

	int posX = (cursorPosition.x - rect.left - 9) / 6;
	int posY = (cursorPosition.y - rect.top - 32) / 6;

	return { posX , posY };
}

void Application::Input() {
	if ((GetKeyState(VK_RETURN) & 0x8000))
		isOpen = false;

}

void Application::Update() {
	polygon.RotateByDegrees(1);
}

void Application::Draw() {
	console.Clear();

	polygon.Draw();
	POINT cursor = GetCursorPosition();
	Drawable::ColorPixel(cursor.x, cursor.y, 7);
	
	console.Display();
}