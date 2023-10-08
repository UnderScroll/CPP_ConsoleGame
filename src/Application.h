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

	std::vector<std::unique_ptr<GameObject>> _game_objects;

	POINT GetCursorPosition();

	static POINT cursor;
	static Application instance;

	unsigned long long frameCount = 0;	
};

}

