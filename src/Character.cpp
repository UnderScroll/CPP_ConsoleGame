#include "Character.h"
#include "Console.h"

void Character::Draw(Console& console) {
	console.buffer[pos.y][pos.x].Char.UnicodeChar = 0x2588;
}