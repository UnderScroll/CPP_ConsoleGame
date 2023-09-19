#include "Character.h"
#include "Console.h"

void Character::draw(Console& console) {
	console.buffer[5][10].Char.AsciiChar = 'H';
}