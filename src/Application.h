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

	static void AddGameObject(std::unique_ptr<GameObject> unique)
	{
		GetInstance()._game_objects.push_back(unique);
	}
	
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

	std::vector<std::unique_ptr<GameObject>> _game_objects;

	static Application instance;

	unsigned long long frameCount = 0;	
};