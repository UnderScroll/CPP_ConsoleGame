#pragma once
#include "Console.h"

#include <chrono>
#include <fstream>

#include "PolygonObject.h"

class Application {
public:
	static void Run() { instance.InstanceRun(); };

	static Application& GetInstance() { return instance; }
private:
	Application() {};

	void InstanceRun();

	void Setup();
	void Input();
	void Update();
	void Draw();

	bool isOpen;
	Console& console = Console::GetInstance();
	PolygonObject polygon;

	static Application instance;

	unsigned long long frameCount = 0;
	std::ofstream ofstream = std::ofstream("res/runtime.log");
};