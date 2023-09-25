#pragma once
#include "Console.h"

#include <chrono>
#include <fstream>
#include <vector>

#include "GameObject.h"

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

	std::vector<std::shared_ptr<GameObject>> _game_objects;

	static Application instance;

	unsigned long long frameCount = 0;	
};