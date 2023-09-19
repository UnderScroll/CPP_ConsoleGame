#include "Character.h"
#include "Console.h"

void Character::Draw(Console& console) {
	/*console.buffer[5][10].Char.UnicodeChar = 0x2588;
	console.buffer[5][10].Attributes = 0x0001;

	console.buffer[5][11].Char.UnicodeChar = 0x2588;
	console.buffer[5][11].Attributes = 0x0007;*/

	console.buffer[5][12].Char.UnicodeChar = 0x2588;
	console.buffer[5][12].Attributes = 0x0002;

}