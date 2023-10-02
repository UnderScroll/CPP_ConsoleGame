#include "Application.h"

#include <iostream>
#include <thread>

#include "Vector2.h"
#include "PolygonObject.h"
#define MIN_FRAMETIME_MS 10

Application Application::instance = Application();
std::ofstream Application::ofstream = std::ofstream("res/runtime.log");

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
	auto pol1 = PolygonObject::CreatePolygon(points, 0x0007);
	pol1->MoveTo(Vector2(30, 30));
}

void Application::Input() {
	/*
	if (GetKeyState(VK_RETURN) & 0x8000) {
		ofstream << "[INFO] - " << frameCount << " - VK_RETURN" << std::endl;
	}
	if (GetKeyState(VK_ESCAPE) & 0x8000) {
		ofstream << "[INFO] - " << frameCount << " - VK_ESCAPE" << std::endl;
		isOpen = false;
	}
	*/
}

void Application::Update() {
	for(auto itr=_game_objects.begin();itr!=_game_objects.end();++itr)
	{
		if(!(*itr)->_destroyed)
		{
			(*itr)->Update();
		}
		else {
			_game_objects.erase(itr);
		}	
	}
}

void Application::Draw() {
	console.Clear();

	for(auto game_object : _game_objects)
	{
		game_object->Draw();
	}
	
	console.Display();
}