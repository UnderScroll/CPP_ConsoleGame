#pragma once
#include "Console.h"

#include <chrono>
#include <fstream>

#include "PolygonObject.h"

class Application {
public:
	static void Run() { GetInstance().InstanceRun(); };

	static Application& GetInstance() { return instance; }

	static std::ofstream ofstream;



private:
	Application() {};
	Application(const Application& other);
	~Application();

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
};