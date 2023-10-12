#pragma once
#include "Application.h"

#include <iostream>
#include <thread>

#include "Vector2.h"
#include "RotatingObject.h"
#include "Polygon.h"
#include "Rectangle.h"
#include "GameObject.h"

#define MIN_FRAMETIME_MS 16

namespace core {

Application Application::instance = Application();
std::ofstream Application::ofstream = std::ofstream("res/runtime.log");
POINT Application::cursor = { 0, 0 };

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
		ofstream << "[INFO] Colliders : \n";
		for (Collider*& collider : Collider::colliders)
			ofstream << "\t" << collider  << std::endl;
		ofstream << "[INFO] Frame : " << frameCount << " - " << "frameTime : " << std::chrono::duration_cast<std::chrono::milliseconds>(frameEnd - frameStart).count() << "ms" << std::endl;
	}
}

void Application::Setup() {
	console.Setup();
	isOpen = true;
	std::vector<Vector2> points;
	points.push_back(Vector2(-10, -10));
	points.push_back(Vector2(10, -10));
	points.push_back(Vector2(0, 10));

	Rectangle rect = Rectangle(10, 10);
	rect._color = 1;
	rect.MoveBy({ 10, 10 });

	auto triangle=Polygon(points,true);
	triangle.SetLocalPosition(Vector2(0,25));
	//rect.AddChild<Polygon>(triangle);

	auto rotating = RotatingObject(30,30,1);
	//rotating.AddChild<Rectangle>(rect);

	GameObject::AddGameObjectToRoot<RotatingObject>(rotating);
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

	cursor = GetCursorPosition();
}

void Application::Update()
{
	GameObject::UpdateGameObjectPointersList(GameObject::_rootGameObjects);
}

void Application::Draw() {
	console.Clear();
	
	GameObject::UpdateGameObjectPointersList(GameObject::_rootGameObjects);

	Drawable::ColorPixel(cursor.x, cursor.y, 7);
	
	console.Display();
}

}
