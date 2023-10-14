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
#include "Collider.h"
#include "Ray.h"

#define MIN_FRAMETIME_MS 16

namespace core {

Application Application::instance = Application();
std::ofstream Application::ofstream = std::ofstream("res/runtime.log");
POINT Application::cursor = { 0, 0 };


Collider c0;
Collider c1;
Ray laser;
Ray otherLaser;

std::vector<Ray::CollisionInfo> collisionInfos;

double distSqrd(Vector2 a, Vector2 b) {
	return (b._x - a._x) * (b._x - a._x) + (b._y - a._y) * (b._y - a._y);
}

Application::~Application() {
	ofstream.close();
}

void Application::InstanceRun() {
	Setup();
	while (isOpen) {
		auto waitTime = std::chrono::steady_clock::now() + std::chrono::milliseconds(MIN_FRAMETIME_MS);
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
	isOpen = true;
	std::vector<Vector2> points;
	points.push_back(Vector2(-10, -10));
	points.push_back(Vector2(10, -10));
	points.push_back(Vector2(0, 10));

	Rectangle rect = Rectangle(10, 10);
	rect._color = 1;
	rect.MoveBy({ 10, 10 });

	auto triangle=Polygon(points,true);
	auto rotating = RotatingObject(30,30,3);

	auto rotatingPtr=GameObject::AddGameObjectToRoot<RotatingObject>(rotating);
	auto rectPtr=rotatingPtr->AddChild<Polygon>(rect);
	rectPtr->SetLocalPosition({ 0, 0 });
	auto triPtr=rectPtr->AddChild<Polygon>(triangle);
	triPtr->SetLocalPosition({ 0, 12 });
	triPtr->SetLocalScale({ 0.5, 0.5 });
	rotatingPtr->SetLocalScale({ 2,2 });

	auto rotatingPtr2=GameObject::AddGameObjectToRoot<RotatingObject>(RotatingObject(100,50,1));

	auto textPtr = rotatingPtr2->AddChild<TextObject>(TextObject(7, 1,1));
	textPtr->SetText("Hello");
	textPtr->SetLocalPosition({ 0, 0 });
	textPtr->SetLocalScale({ 8, 8 });

	std::vector<Vector2> c0points = { Vector2(10, 10), Vector2(90, 10), Vector2(90, 90), Vector2(10 , 90) };
	c0 = Collider(Polygon(c0points, false));

	std::vector<Vector2> c1points = { Vector2(30, 100), Vector2(80, 100),  Vector2(80, 80) };
	c1 = Collider(Polygon(c1points, true));

	laser = Ray(Vector2(20, 20), Vector2(0.5, 0.3));

	otherLaser = Ray(Vector2(50, 50), Vector2(0.3, -0.8));
}

POINT Application::GetCursorPosition() {
	POINT cursorPosition;

	GetCursorPos(&cursorPosition);

	RECT rect;
	GetWindowRect(Console::windowHandle, &rect);

	int posX = (cursorPosition.x - rect.left - 9) / 6;
	int posY = (cursorPosition.y - rect.top - 32) / 6;

	return { posX , posY };
}

void Application::Input() {
	if ((GetKeyState(VK_RETURN) & 0x8000))
		isOpen = false;

	cursor = GetCursorPosition();
}

void Application::Update()
{
	GameObject::UpdateGameObjectPointersList(GameObject::_rootGameObjects);

	laser.direction = Vector2(cursor.x - laser.position._x, cursor.y - laser.position._y);

	collisionInfos.clear();
	std::vector<Ray::CollisionInfo> c0Infos = laser.cast(c0);
	std::vector<Ray::CollisionInfo> c1Infos = laser.cast(c1);
	Ray::CollisionInfo rayCollisionInfo = laser.cast(otherLaser);

	collisionInfos.reserve(c0Infos.size() + c1Infos.size() + 1);

	collisionInfos.insert(collisionInfos.end(), c0Infos.begin(), c0Infos.end());
	collisionInfos.insert(collisionInfos.end(), c1Infos.begin(), c1Infos.end());
	collisionInfos.push_back(rayCollisionInfo);
}

void Application::Draw() {
	console.Clear();
	
	GameObject::DrawRootGameObjects();

	Drawable::ColorPixel(cursor.x, cursor.y, 7);
	Drawable::DrawLine(laser.position, laser.position + Vector2(laser.direction._x * 100, laser.direction._y * 100), 3);
	
	//Closest Collision Point
	double minDistSqrd = distSqrd(laser.position, collisionInfos[0].point);
	Ray::CollisionInfo minDistInfo = collisionInfos[0];

	//Draw all collisionPoints with ray
	for (Ray::CollisionInfo& info : collisionInfos) {

		switch (info.type) {
		case Collider::CollisionType::OutOfBounds:
			break;
		case Collider::CollisionType::Wall:
			Drawable::ColorPixel(info.point._x, info.point._y, 2);
			break;
		case Collider::CollisionType::Ray:
			Drawable::ColorPixel(info.point._x, info.point._y, 1);
			break;
		}

		if (info.type != Collider::CollisionType::OutOfBounds) {
			double currentDistSqrd = distSqrd(laser.position, info.point);
			if (minDistSqrd > currentDistSqrd) {
				minDistSqrd = currentDistSqrd;
				minDistInfo = info;
			}
		}
	}

	console.Display();
}

}
