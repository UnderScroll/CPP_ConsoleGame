#include "TextObject.h"
#include "Polygon.h"

namespace core
{
	std::map<char, std::vector<Vector2>> TextObject::_charPolygons = TextObject::CreatCharPolygons();

	void TextObject::SetText(std::string text)
	{
		_text = text;
		_children.clear();
		float textWidth = text.size() * (CHAR_WIDTH)+(text.size() - 1) * _spacing;
		float textIncrement = (CHAR_WIDTH + _spacing);
		float textStartX = -textWidth / 2;

		for (int i = 0; i < _text.size(); i++)
		{
			char c = std::toupper(_text[i]);

			if (c == ' ')
				continue;

			if(_charPolygons.contains(c) == false)
				continue;

			auto polygonPtr = AddChild<Polygon>(Polygon());
			polygonPtr->SetLocalPosition(Vector2(textStartX + i * textIncrement, 0));
			polygonPtr->_isClosed = false;
			polygonPtr->_color = _color;

			for(auto point : _charPolygons.at(c))
			{
				if (point == SNONE) {
					polygonPtr= AddChild<Polygon>(Polygon());
					polygonPtr->SetLocalPosition(Vector2(textStartX + i * textIncrement, 0));
					polygonPtr->_isClosed = false;
					polygonPtr->_color = _color;
					continue;
				}
				polygonPtr->_points.push_back(point*Vector2(1,1.8f));
			}
		}
	}

	void TextObject::SetColor(Color color)
	{
		_color = color;
		SetText(_text);
	}

	void TextObject::SetAlpha(float alpha)
	{
		_alpha = alpha;
		SetText(_text);
	}

	std::vector<Vector2> TextObject::GetPointsForLetter(char letter, int part) {
		//For letters in multiple part like the X
		std::vector<Vector2> points = _charPolygons.at(letter);
		std::vector<std::vector<Vector2>> pointsVectors = std::vector<std::vector<Vector2>>();

		std::vector<Vector2> currentPointsVector = std::vector<Vector2>();
		for (auto point : points) {
			if (point == SNONE) {
				pointsVectors.push_back(currentPointsVector);
				currentPointsVector = std::vector<Vector2>();
				continue;
			}
			currentPointsVector.push_back(point);
		}
		pointsVectors.push_back(currentPointsVector);

		int index= ((part+1) % (pointsVectors.size()))-1;
		return pointsVectors[part % currentPointsVector.size()];
	}

	TextObject::TextObject(Color color, float alpha, float spacing) :_color(color), _alpha(alpha), _spacing(spacing) {}

	void TextObject::SetSpacing(float spacing)
	{
		_spacing = spacing;
		SetText(_text);
	}
}
