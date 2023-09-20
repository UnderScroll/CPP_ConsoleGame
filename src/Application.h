#pragma once
#include "Console.h"
#include "Character.h"
#include <chrono>
#include <fstream>

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

	bool isOpen = true;
	Console console;
	Character character;

	static Application instance;

	unsigned long long frameCount = 0;
	std::ofstream ofstream = std::ofstream("res/runtime.log");
};