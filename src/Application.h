#pragma once
#include "Console.h"

#include <chrono>
#include <fstream>
#include <vector>

#include "GameObject.h"
#include "PolygonObject.h"
#include "Laser.h"

class Application {
public:
	static void Run() { GetInstance().InstanceRun(); };

	static Application& GetInstance() { return instance; }

	static std::ofstream ofstream;

	static void AddGameObject(std::shared_ptr<GameObject> game_object_ptr)
	{
		GetInstance()._game_objects.push_back(game_object_ptr);
	}
	
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

	std::vector<std::shared_ptr<GameObject>> _game_objects;

	POINT GetCursorPosition();

	static Application instance;

	unsigned int inputs;

	unsigned long long frameCount = 0;	
};