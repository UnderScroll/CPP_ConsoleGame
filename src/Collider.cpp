#include "Collider.h"

#include "Application.h"

namespace core {

std::vector<Collider*> Collider::colliders = std::vector<Collider*>();

Collider::Collider() {
	Application::ofstream << "[INFO] Collider Constructor : " << this << std::endl;
	colliders.push_back(this);
}

Collider::~Collider() {
	Application::ofstream << "[INFO] Collider Destructor : " << this << std::endl;
	auto this_it = std::find(colliders.begin(), colliders.end(), this);
	if (this_it != colliders.end())
		colliders.erase(this_it);
}

}

