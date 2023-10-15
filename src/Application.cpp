#pragma once
#include "Application.h"

#include <iostream>
#include <thread>

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

namespace core {

Application Application::_instance = Application();
std::ofstream Application::ofstream = std::ofstream("res/runtime.log");
Vector2 Application::_cursor = { 0, 0 };
bool Application::_clickDown = false;
bool Application::_clickPressed = false;
float Application::_horizontalAxis = 0;

void MouseInputThread(int& r_scrollWheel);

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
	_isOpen = true;

	std::vector<Vector2> points;
	points.push_back(Vector2(-10, -10));
	points.push_back(Vector2(10, -10));
	points.push_back(Vector2(0, 10));

	Rectangle rect = Rectangle(10, 10);
	rect._color = Drawable::WHITE;
	rect.MoveBy({ 10, 10 });

	auto triangle=Polygon(points,true);
	auto rotating = RotatingObject(30,30,3);

	auto rotatingPtr=GameObject::AddGameObjectToRoot<RotatingObject>(rotating);
	
	auto movablePtr=GameObject::AddGameObjectToRoot<MovableObject>(MovableObject());
	auto movablePtr2=GameObject::AddGameObjectToRoot<MovableObject>(MovableObject());
	auto rectPtr = movablePtr2->AddChild<Polygon>(rect);
	rectPtr->SetLocalPosition({ 0, 0 });

	auto triPtr=movablePtr->AddChild<Polygon>(triangle);


	triPtr->SetLocalPosition({ 0, 0 });
	triPtr->SetLocalScale({ 0.5, 0.5 });
	triPtr->_color = Drawable::Color::RED;
	rotatingPtr->SetLocalScale({ 2,2 });

	auto uiBackGroundPtr = GameObject::AddGameObjectToRoot<HorizontalLayoutGroup>(HorizontalLayoutGroup(Vector2((WIDTH / 2)+2, 24),10, Drawable::Color::BLACK, Drawable::Color::WHITE, true, UIRect::BackgroundFill));
	uiBackGroundPtr->SetLocalPosition({ WIDTH / 4-1, HEIGHT - 12 });

	auto button = uiBackGroundPtr->AddElement<MovableObjectButton>(MovableObjectButton(Vector2(WIDTH / 5, 20), Drawable::Color::WHITE, Drawable::LIGHTER_WHITE, Drawable::GRAY,movablePtr, Drawable::Color::BLACK, Drawable::Color::CYAN,true, UIRect::BackgroundFill));
	button->SetPreview(*triPtr,Drawable::BLACK);

	auto button2 = uiBackGroundPtr->AddElement<MovableObjectButton>(MovableObjectButton(Vector2(WIDTH / 5, 20), Drawable::Color::WHITE, Drawable::LIGHTER_WHITE, Drawable::GRAY, movablePtr2, Drawable::Color::BLACK, Drawable::Color::CYAN, true, UIRect::BackgroundFill));
	button2->SetPreview(*rectPtr, Drawable::BLACK);

	auto button3 = uiBackGroundPtr->AddElement<MovableObjectButton>(MovableObjectButton(Vector2(WIDTH / 5, 20), Drawable::Color::WHITE, Drawable::LIGHTER_WHITE, Drawable::GRAY, movablePtr2, Drawable::Color::BLACK, Drawable::Color::CYAN, true, UIRect::BackgroundFill));
	button3->SetPreview(*rectPtr, Drawable::BLACK);

	auto rotatingPtr2=GameObject::AddGameObjectToRoot<RotatingObject>(RotatingObject(100,50,1));

	auto textPtr = rotatingPtr2->AddChild<TextObject>(TextObject(Drawable::WHITE, 1,1));
	textPtr->SetText("Hello");
	textPtr->SetLocalPosition({ 0, 0 });
	textPtr->SetLocalScale({ 8, 8 });
}

void Application::ComputeCursorPosition() {
	POINT cursorPosition;

	GetCursorPos(&cursorPosition);

	RECT rect;
	GetWindowRect(Console::windowHandle, &rect);

	int posX = (cursorPosition.x - rect.left - 9) / 6;
	int posY = (cursorPosition.y - rect.top - 32) / 6;

	_cursor= Vector2(posX , posY);
}

void Application::Input() {
	if ((GetKeyState(VK_RETURN) & 0x8000))
		_isOpen = false;

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

}
