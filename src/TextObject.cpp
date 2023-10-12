#include "TextObject.h"

void TextObject::SetText(std::string text)
{
	_text = text;
	_children.clear();
	for (int i = 0; i < _text.size(); i++)
	{
		char c = _text[i];
		if (c == ' ')
			continue;
		
	}
}

void TextObject::SetColor(int color)
{
	_color = color;
	SetText(_text);
}

void TextObject::SetAlpha(float alpha)
{
	_alpha = alpha;
	SetText(_text);
}

void TextObject::SetFontWidth(int size)
{
	_fontWidth = size;
	SetText(_text);
}
