#pragma once
#include "Console.h"
#include "Character.h"
#include <chrono>

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
	std::chrono::steady_clock clock;
};