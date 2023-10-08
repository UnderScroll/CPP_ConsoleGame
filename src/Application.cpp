#include "Application.h"

#include <iostream>
#include <thread>

#include "Vector2.h"
#include "RotatingObject.h"
#include "Polygon.h"
#include "Rectangle.h"

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

	_game_objects.push_back(std::make_unique<Rectangle>(rect));

	//auto pol1=PolygonObject::CreatePolygon(points, 0x0007);
	//pol1->MoveTo(Vector2(30,30));
	//auto triangle=Polygon::CreatePolygon(points,true);
	//triangle->SetLocalPosition(Vector2(0,25));
	//rectangle->AddChild(triangle);
	
	//auto rotating = RotatingObject::CreateRotatingObject(30,30,1,rectangle);

	//rectangle->SetLocalPosition(Vector2(0, 0));
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
	for (auto& game_object : _game_objects)
	{
		game_object->RotateByDegrees(0.1);
		game_object->Update();
	}
}

void Application::Draw() {
	console.Clear();
	
	for(auto& game_object : _game_objects)
	{
		game_object->Draw();
	}

	Drawable::ColorPixel(cursor.x, cursor.y, 7);
	
	console.Display();
}

}
