#pragma once
#include <chrono>
#include <fstream>
#include <vector>

#include "Console.h"
#include "GameObject.h"
#include "Laser.h"

#define MIN_FRAMETIME_MS 16

namespace core {

	class Application {
	public:
		static void Run() { GetInstance().InstanceRun(); };

		static Application& GetInstance() { return _instance; }

		static std::ofstream ofstream;

		static Vector2 GetCursorPosition() { return _cursor; }
		static bool GetClickDown() { return _clickDown; }
		static bool GetClickPressed() { return _clickPressed; }
		static float GetScrollWheel() { return _scrollWheel; }

	private:
		Application() : _isOpen(true) {};
		Application(const Application& other);
		~Application();

		static std::chrono::steady_clock::time_point GetWaitTime() {
			return  std::chrono::steady_clock::now() + std::chrono::milliseconds(MIN_FRAMETIME_MS);
		}

		void InstanceRun();

		void Setup();
		void Input();
		void MouseInputThread();
		std::thread _mouseThread;
		void Update();
		void Draw();

		bool _isOpen;
		Console& console = Console::GetInstance();

		static Vector2 _cursor;
		static bool _clickDown;
		//Click pressed is only true on the frame where the player release the click, like in Unity
		static bool _clickPressed;
		static float _scrollWheel;
		static Application _instance;

		unsigned long long frameCount = 0;

		static void ComputeCursorPosition();
	};

}

