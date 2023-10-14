#include "Collider.h"

namespace core {

Collider::Collider(CollisionType collisionType): type(collisionType) {
	collisionShape = Polygon();
}

Collider::Collider(Polygon collisionShape, CollisionType collisionType): collisionShape(collisionShape), type(collisionType) {

}

}