#pragma once
#include <vector>

#include "GameObject.h"
#include "Vector2.h"

namespace core {

	class Polygon :
		public GameObject
	{
	public:
		std::vector<Vector2> _points; //Coordinates are relatives to the position of the GameObject
		float _alpha;
		bool _isClosed;

		virtual Vector2 GetBoundingBox() override;
		virtual float GetDiameter() override;

		virtual void Draw() override;
		void RotateToRadians(float targetAngle);

		virtual void SetLocalScale(Vector2 targetScale) override;

		void OnCreationOver() override;

		virtual void Update() override {}

		Polygon() : _alpha(1), _isClosed(true) {
			_color = WHITE;
		};

		Polygon(std::vector<Vector2> points, bool isClosed, Color color = WHITE, float alpha = 1, Vector2 localPosition = Vector2(0, 0), Vector2 localScale = Vector2(1, 1), float localRotation = 0) :_points(points),
			_alpha(alpha), _isClosed(isClosed), _computedPoints(_points)
		{
			_color = color;
			_localPosition = localPosition;
			_localScale = localScale;
			_localRotation = localRotation;
		};

		void virtual Destroy() override {
			GameObject::Destroy();
			//iterate over polygons to find a shared_ptr to this one and erase it
			for (auto itr = _polygons.begin(); itr != _polygons.end(); ++itr)
			{
				if ((*itr) != shared_from_this()) continue;
				_polygons.erase(itr);
				break;
			}
		}

		static std::vector<std::shared_ptr<Polygon>> GetPolygons() {
			return _polygons;
		};

	protected:
		std::vector<Vector2> _computedPoints;
		void ComputePoints();
		static std::vector<std::shared_ptr<Polygon>> _polygons;
	};

}
