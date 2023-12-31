#include "Laser.h"

#include <limits>

#include "Application.h"
#include "SoundManager.h"
#undef max
#define MAX_REFLECTIONS 20
//When we reflect the laser, we should start the reflected ray a bit further from the reflection point, to avoid colliding with the same surface again, this is this distance.
#define REFLECTION_SAFETY_DISTANCE 0.01

namespace core {

	std::vector<Collider> Laser::s_colliders = std::vector<Collider>();

Laser::Laser(Vector2 position, Vector2 direction) 
	: _position(position), _direction(direction) 
{
	_laserBase = Polygon({ Vector2(-3, 4), Vector2(4, 0) , Vector2(-3, -4) }, true);
	
	//_laserBase.RotateToRadians(atan2(_direction._x, _direction._y));

	_laserBeam._color = Drawable::Color::RED;
	_laserBeam._isClosed = false;
}

void Laser::computeBeam(std::vector<Collider>& colliders) {
	_laserBeam._points.clear();

	Ray initialRay = Ray(_position, _direction);
	_laserBeam._points.push_back(_position);

	computeBeamRec(colliders, initialRay, 0);
}

Ray computeReflectedRay(std::pair<Vector2, Vector2> surface, Ray& ray, Vector2& reflectionPoint) {
	Vector2 normal = Vector2(-(surface.second._y - surface.first._y), surface.second._x - surface.first._x).Normalized();
	Vector2 incident = ray._direction.Normalized();

	double incidentDotNormal = incident.dot(normal);

	Vector2 reflectedRayDir = Vector2(incident._x - 2 * incidentDotNormal * normal._x, incident._y - 2 * incidentDotNormal * normal._y);

	return Ray(reflectionPoint+ REFLECTION_SAFETY_DISTANCE * reflectedRayDir, reflectedRayDir);
}

double Laser::GetDiameter()
{
	return _laserBase.GetDiameter();
}

void Laser::computeBeamRec(std::vector<Collider>& colliders, Ray& ray, unsigned int nb_iter) {
	Ray::CollisionInfo closestCollisionPointInfo;
	double minDist = std::numeric_limits<double>().max();

	//Compute all collision points
	for (Collider& collider : colliders) {
		std::vector<Ray::CollisionInfo> collisions = ray.cast(collider);

		for (Ray::CollisionInfo& info : collisions) {
			if (!info.hasCollided)
				continue;

			double dist = distSqrd(ray._position, info.point);
			if (minDist > dist) {
				minDist = dist;
				closestCollisionPointInfo = info;
			}
		}
	}

	if (!closestCollisionPointInfo.hasCollided) {
		_laserBeam._points.push_back(ray._position + (ray._direction * 1000));
		return;
	}
	else {
		_laserBeam._points.push_back(closestCollisionPointInfo.point);
	}

	if (closestCollisionPointInfo.collider->_isReflective && nb_iter < 20) {
		Ray reflectedRay = computeReflectedRay(closestCollisionPointInfo.collisionSurface, ray, closestCollisionPointInfo.point);

		computeBeamRec(colliders, reflectedRay, nb_iter + 1);
	}
	else {
		if (closestCollisionPointInfo.collider->_type == Collider::Type::Sensor) {
			//TO DO : Add audio and/or visual feedbacks
			_sensor = closestCollisionPointInfo.collider;
			SoundManager::PlayPoweringUpSound(_sensor->chargeLevel / 99.0);
			if (++_sensor->chargeLevel > 100) {
				Application::LoadNextLevel();
				return;
			}	
			if (_sensorLevelDisplayer.expired()) return;
			_sensorLevelDisplayer.lock()->_alpha=(_sensor->chargeLevel / 99.0);
		}
		else {
			if (_sensor != nullptr) _sensor->chargeLevel = 0;
		}
	}
}

void Laser::Update() {	
	_laserBase.SetWorldPosition(_position);
	_laserBase.RotateToRadians(GetLocalRotationInRadians());
	
	_direction = Vector2(cos(GetLocalRotationInRadians()), sin(GetLocalRotationInRadians()));

	//Each collision creates a point, we remove the start and end point and badabim badaboom, we get the number of collisions	
	// I removed the sound effect because it was annoying
	//SoundManager::PlayLaserSound(_laserBeam._points.size() - 2);

	computeBeam(s_colliders);

	_laserBeam.ComputePoints();
}

void Laser::Draw() {
	_laserBeam.Draw();
	_laserBase.Draw();
}

}

