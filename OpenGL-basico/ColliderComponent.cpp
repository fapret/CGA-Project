#include "ColliderComponent.h"

ColliderComponent::ColliderComponent() : EntityComponent("ColliderComponent")
{
	this->transform = new TransformComponent();
}

void ColliderComponent::setFatherEntity(Entity* father)
{
	EntityComponent::setFatherEntity(father);
	std::vector<EntityComponent*> transformList = father->findComponentsByType("TransformComponent");
	if (transformList.size() == 0) {
		father->addComponent(transform);
	}
	else {
		this->transform = (TransformComponent*)transformList.at(0);
	}
}

TransformComponent* ColliderComponent::getTransform()
{
	return transform;
}

void ColliderComponent::draw(float deltaTime)
{
}

void ColliderComponent::setUpCollission(int type, btScalar mass, btScalar scale, bool gravity, glm::vec3 offset)
{
	// Types:
	// 0 Box
	// 1 Plane
	// 2 Sphere
	// 3 Mesh

	btPolyhedralConvexShape* shape = nullptr;
	if (type == 0) {
		btVector3 boxSize(scale, scale, scale);
		shape = new btBoxShape(boxSize);
		btScalar newMargin = scale;
		shape->setMargin(newMargin);
	}
	
	// Set the initial position and orientation of the box
	btTransform boxTransform;
	boxTransform.setIdentity(); // No initial rotation
	glm::vec3 transformPos = this->getTransform()->getPosition() + offset;
	boxTransform.setOrigin(btVector3(transformPos.x, transformPos.y, transformPos.z)); // Initial position

	// Create the motion state
	btDefaultMotionState* boxMotionState = new btDefaultMotionState(boxTransform);

	// Create the rigid body construction info
	btVector3 boxInertia(0, 0, 0);
	shape->calculateLocalInertia(mass, boxInertia);

	this->rigidBody = new btRigidBody(btRigidBody::btRigidBodyConstructionInfo(mass, boxMotionState, shape, boxInertia));

	if (!gravity) {
		this->rigidBody->setGravity(btVector3(0, 0, 0));
	}

	Hierarchy& hierarchy = Hierarchy::getInstance();
	btDiscreteDynamicsWorld* dynamicsWorld = hierarchy.getDynamicsWorld();
	dynamicsWorld->addRigidBody(this->rigidBody);

}

btRigidBody* ColliderComponent::getRigidBody()
{
	return rigidBody;
}

#ifdef USE_IMGUI
void ColliderComponent::EditorPropertyDraw()
{
	EntityComponent::EditorPropertyDraw();
}
#endif
