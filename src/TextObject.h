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
#define SNONE Vector2(1000,1000)
#define CHAR_WIDTH 1.0f

namespace core 
{
	class TextObject :
		public GameObject
	{
	public:
		// Inherited via GameObject
		void SetText(std::string text);
		void SetColor(Color color);
		void SetAlpha(float alpha);
		void SetSpacing(float spacing);

		std::string GetText() const { return _text; }
		Color GetColor() const { return _color; }
		float GetAlpha() const { return _alpha; }
		float GetSpacing() const { return _spacing; }

		static std::vector<Vector2> GetPointsForLetter(char letter, int part=0);

		TextObject(Color color = WHITE, float alpha = 1, float spacing = 0.1f);;
	private:
		std::string _text;
		Color _color;
		float _alpha;
		float _spacing;

		static std::map<char, std::vector<Vector2>> _charPolygons;

		static std::map<char, std::vector<Vector2>> CreatCharPolygons()
		{
			std::map<char, std::vector<Vector2>> m;
			m['A'] = { S1, S4,S6,S4,S8, S6,S3 };
			m['B'] = { S1, S7,S9,S5,S4,S5,S3,S1 };
			m['C'] = { S9, S8,S4,S2,S3 };
			m['D'] = { S1, S2,S6,S8,S7,S1 };
			m['E'] = { S1, S7,S9,S7,S4,S6,S4,S1,S3 };
			m['F'] = { S1, S7,S9,S7,S4,S6 };
			m['G'] = { S8, S4,S2,S6,S5 };
			m['H'] = { S1, S7,S4,S6,S9,S3 };
			m['I'] = { S1,S3, S2,S8 ,S9,S7 };
			m['J'] = { S7,S9,S8,S2,S4 };
			m['K'] = { S1,S7,S4,S9,S4,S3 };
			m['L'] = { S7,S1,S3 };
			m['M'] = { S1,S7,S5,S9,S3 };
			m['N'] = { S1,S7,S3,S9 };
			m['O'] = { S2,S4,S8,S6,S2};
			m['P'] = { S1,S7,S9,S5,S4 };
			m['Q'] = { S2,S4,S8,S6,S2,SNONE,S5,S3 };
			m['R'] = { S1,S7,S9,S5,S4,S5,S3 };
			m['S'] = { S9,S7,S4,S6,S3,S1 };
			m['T'] = { S7,S9,S8,S2 };
			m['U'] = { S7,S1,S3,S9 };
			m['V'] = { S7,S2,S9 };
			m['W'] = { S7,S1,S5,S3,S9 };
			m['X'] = { S1,S9,SNONE,S7,S3 };
			m['Y'] = { S7,S5,S9,S5,S2 };
			m['Z'] = { S7,S9,S1,S3 };
			m['!'] = { S8,S5,SNONE,S2,S2-Vector2(0,0.1f)};
			m['\'']= { S8,S8+Vector2(-0.2f,0.2f)};

			return m;
		}
	};
}

