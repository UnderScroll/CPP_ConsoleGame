#pragma once
#include <chrono>
#include <fstream>
#include <vector>

#include "Console.h"
#include "GameObject.h"
#include "Laser.h"

namespace core {

class Application {
public:
	static void Run() { GetInstance().InstanceRun(); };

	static Application& GetInstance() { return _instance; }

	static std::ofstream ofstream;

	POINT GetCursorPosition();

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

	static POINT cursor;
	static Application _instance;

	unsigned long long frameCount = 0;	
};

}

