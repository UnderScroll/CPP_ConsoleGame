#include "Collider.h"

namespace core {
Collider::Collider(Polygon collisionShape, Type collisionType, bool isReflective): _collisionShape(collisionShape), _type(collisionType), _isReflective(isReflective) {

}

}