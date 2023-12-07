#include "CollisionComponent.h"

void CollisionComponent::setDynamicsWorld(btDiscreteDynamicsWorld* dynamicsWorld)
{
	this->dynamicsWorld = dynamicsWorld;
}

void CollisionComponent::setGravity() {
	this->dynamicsWorld->setGravity(btVector3(0, -9.8, 0));
}
