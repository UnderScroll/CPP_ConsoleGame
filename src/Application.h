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

	enum Keys {
		ENTER_KEY_PRESSED = 0b0001,
		ESCAPE_KEY_PRESSED = 0b0010,
		LEFT_MOUSE_BUTTON_PRESSED = 0b0100 
	};
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

	POINT GetCursorPosition();

	static Application instance;

	unsigned int inputs;

	unsigned long long frameCount = 0;	
};