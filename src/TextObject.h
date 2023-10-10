#pragma once
#include "GameObject.h"
#include <map>

//These defines are used to quickly draw all the letters. Each segments is one of the 9 points usable as vertices for a letter. To understand what segments if what point, look at a numpad
#define S7 Vector2(-0.5f, -0.5f)
#define S8 Vector2(0, -0.5f)
#define S9 Vector2(0.5f, -0.5f)
#define S4 Vector2(-0.5f, 0)
#define S5 Vector2(0, 0)
#define S6 Vector2(0.5f, 0)
#define S1 Vector2(-0.5f, 0.5f)
#define S2 Vector2(0, 0.5f)
#define S3 Vector2(0.5f, 0.5f)

class TextObject :
    public GameObject
{
public:
	// Inherited via GameObject
	virtual void Draw() override;
	virtual void Update() override;

	void SetText(std::string text);
	void SetColor(int color);
	void SetAlpha(float alpha);
	void SetFontWidth(int size);

	std::string GetText() const;
	int GetColor() const;
	float GetAlpha() const;
	int GetFontWidth() const;
private:
	std::string _text;
	int _color;
	float _alpha;
	int _fontWidth;
	Vector2 _position;

	static const std::map<char, std::vector<Vector2>> _chars_polygons;

	static std::map<char, std::vector<Vector2>> CreatCharPolygons()
	{
		std::map<char, std::vector<Vector2>> m;
		m['A'] = { S1, S4,S6,S4,S8, S6,S3 };
		m['B'] = { S1, S7,S9,S5,S4,S5,S3,S1 };
		m['C'] = { S9, S8,S4,S2,S3 };
		m['D'] = { S1, S2,S6,S8,S7,S1};

		return m;
	}
};

const std::map<char, Vector2[]> = CreateCharPolygons();

