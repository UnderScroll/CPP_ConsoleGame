#pragma once
#include <vector>

namespace core {

class Collider {
public:
	Collider();
	~Collider();

	static std::vector<Collider*> colliders;
};

}

