#pragma once
#include "Console.h"

#include <chrono>
#include <fstream>

#include "PolygonObject.h"
#include "Laser.h"

class Application {
public:
	static void Run() { GetInstance().InstanceRun(); };

	static Application& GetInstance() { return instance; }

	static std::ofstream ofstream;

private:
	Application(): isOpen(true) {};
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
	Laser laser = Laser(10);

	POINT GetCursorPosition();

	static Application instance;

	unsigned int inputs;

	unsigned long long frameCount = 0;	
};