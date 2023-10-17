#pragma once
#include "Application.h"

#include <iostream>
#include <thread>

#include "SoundManager.h"
#include "Vector2.h"
#include "RotatingObject.h"
#include "Polygon.h"
#include "Rectangle.h"
#include "GameObject.h"
#include "TextObject.h"
#include "UIRect.h"
#include "Button.h"
#include "MovableObject.h"
#include "MovableObjectButton.h"
#include "HorizontalLayoutGroup.h"
#include "Levels/Level1.h"
#include "Levels/Level2.h"
#include "Levels/Level3.h"
#include "Levels/Level4.h"
#include "Levels/Level5.h"
#include "Levels/LevelMainMenu.h"
#include "Levels/LevelEndMenu.h"

namespace core {

Application Application::_instance = Application();
std::ofstream Application::ofstream = std::ofstream("res/runtime.log");
Vector2 Application::_cursor = { 0, 0 };
bool Application::_clickDown = false;
bool Application::_clickPressed = false;
float Application::_horizontalAxis = 0;

Application::~Application() {
	ofstream.close();
}

void Application::InstanceRun() {
	Setup();
	while (_isOpen) {
		auto waitTime = GetWaitTime();
		auto frameStart = std::chrono::steady_clock::now();
		
		Input();
		Update();
		Draw();

		std::this_thread::sleep_until(waitTime);
		frameCount++;

		auto frameEnd = std::chrono::steady_clock::now();
		ofstream << "[INFO] Frame : " << frameCount << " - " << "frameTime : " << std::chrono::duration_cast<std::chrono::milliseconds>(frameEnd - frameStart).count() << "ms" << std::endl;
	}
}

void Application::Setup() {
	console.Setup();
	SoundManager::Setup();
	_isOpen = true;

	_currentLevelIndex = 0;

	AddLevel<levels::LevelMainMenu>();
	//AddLevel<levels::Level1>();
	//AddLevel<levels::Level2>();
	//AddLevel<levels::Level3>();
	//AddLevel<levels::Level4>();
	AddLevel<levels::Level5>();
	AddLevel<levels::LevelEndMenu>();

	LoadLevel(_currentLevelIndex);
}

void Application::ComputeCursorPosition() {
	POINT cursorPosition;

	GetCursorPos(&cursorPosition);

	RECT rect;
	GetWindowRect(Console::windowHandle, &rect);

	//Offsets the cursor position from window pos + borders and rectify by char size
	int posX = (cursorPosition.x - rect.left - 9) / 6;
	int posY = (cursorPosition.y - rect.top - 32) / 6;

	_cursor= Vector2(posX , posY);
}

void Application::Input() {
	_clickPressed = false;
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) 
	{
		_clickDown = true;
	}
	else 
	{
		if (_clickDown) {
			_clickDown = false;
			_clickPressed = true;
		}
	}

	_horizontalAxis = 0;
	//0x51 is the code for the key Q on AZERTY Keyboard and A on QWERTY keyboards
	if (GetAsyncKeyState(VK_LEFT) & 0x8000 || GetAsyncKeyState(0x51) & 0x8000)
		_horizontalAxis -= 1;
	//0x44 is the code for the key D on AZERTY Keyboard and D on QWERTY keyboards
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000 || GetAsyncKeyState(0x44) & 0x8000)
		_horizontalAxis += 1;

	ComputeCursorPosition();
}

void Application::Update()
{
	GameObject::UpdateGameObjectPointersList(GameObject::_rootGameObjects);
}

void Application::Draw() {
	console.Clear();
	
	GameObject::DrawRootGameObjects();

	Drawable::ColorPixel(_cursor._x, _cursor._y, 7);
	
	console.Display();
}

void Application::LoadNextLevel() {
	GetInstance()._currentLevelIndex++;

	if (GetInstance()._currentLevelIndex >= GetInstance()._levels.size()) {
		GetInstance()._currentLevelIndex=0;
	}

	Level::ClearCurrentLevel();
	LoadLevel(GetInstance()._currentLevelIndex);
}

void Application::LoadLevel(int index) {
	GetInstance()._levels[index]->LoadLevel();
}

}
