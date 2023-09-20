#include "Character.h"
#include "Console.h"

void Character::Draw(Console& console) {
	console.buffer[(size_t)_pos._y][(size_t)_pos._x * 2].Char.UnicodeChar = 0x2588;
	console.buffer[(size_t)_pos._y][(size_t)_pos._x * 2 + 1].Char.UnicodeChar = 0x2588;
}