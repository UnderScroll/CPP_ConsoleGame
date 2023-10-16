#include "Collider.h"

namespace core {

Collider::Collider(Type collisionType, bool isReflective): type(collisionType), isReflective(isReflective) {
	collisionShape = Polygon();
}

Collider::Collider(Polygon collisionShape, Type collisionType, bool isReflective): collisionShape(collisionShape), type(collisionType), isReflective(isReflective) {

}

}