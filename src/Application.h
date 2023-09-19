#pragma once
#include "Console.h"

class Application {
public:
	static void run();
private:
	static void setup();
	static void input();
	static void update();
	static void draw();

	static bool isOpen;

	static Console cons;
};