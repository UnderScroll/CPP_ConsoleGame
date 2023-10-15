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

	static POINT GetCursorPosition();
	static bool GetClickDown(){ return _clickDown; }
	static bool GetClickPressed() { return _clickPressed; }

private:
	Application(): _isOpen(true) {};
	Application(const Application& other);
	~Application();

	void InstanceRun();

	void Setup();
	void Input();
	void Update();
	void Draw();

	bool _isOpen;
	Console& console = Console::GetInstance();

	static POINT _cursor;
	static bool _clickDown;
	//Click pressed is only true on the frame where the player release the click, like in Unity
	static bool _clickPressed;
	static Application _instance;

	unsigned long long frameCount = 0;	
};

}

