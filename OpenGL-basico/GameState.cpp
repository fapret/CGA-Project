#include "GameState.h"
#include <string>
#include "Entity.h"
#include "Hierarchy.h"
#include "MeshComponent.h"
#include "TerrainComponent.h"

void loadState()
{
	Hierarchy& hierarchy = Hierarchy::getInstance();
	
	std::string objectName = "City";
	Entity* object = new Entity(objectName);
	hierarchy.addEntity(object);
	MeshComponent* meshComp = new MeshComponent();
	object->addComponent(meshComp);
	meshComp->setFatherEntity(object);
	meshComp->importObject("../models/city.fbx", 20000.0f);
	TransformComponent* tranComp = (TransformComponent*) object->findComponentsByType("TransformComponent").at(0);
	tranComp->setPosition(glm::vec3(0, 250, 0));
	

	std::string objectName2 = "Thanos";
	Entity* object2 = new Entity(objectName2);
	hierarchy.addEntity(object2);
	MeshComponent* meshComp2 = new MeshComponent();
	object2->addComponent(meshComp2);
	ColliderComponent* colliderCompThanos = new ColliderComponent();
	meshComp2->setFatherEntity(object2);
	colliderCompThanos->setFatherEntity(object2);
	
	meshComp2->importObject("../models/thanos.fbx", 2000.0f);
	meshComp2->addAnimation("../models/thanos.fbx");
	TransformComponent* tranCompThanos = (TransformComponent*)object2->findComponentsByType("TransformComponent").at(0);
	tranCompThanos->setPosition(glm::vec3(-25, 230, 100));
	tranCompThanos->setScale(glm::vec3(0.2, 0.2, 0.2));
	colliderCompThanos->setUpCollission(0, 0, 10, false, glm::vec3(0, 10, 0));


	
	std::string objectName3 = "Terrain";
	Entity* terrain = new Entity(objectName3);
	hierarchy.addEntity(terrain);
	TerrainComponent* terrainComp = new TerrainComponent();
	terrain->addComponent(terrainComp);
	terrainComp->setFatherEntity(terrain);
	terrainComp->loadHeightmap("../island_heightmap.png", 10.0f, 0.5f);
	terrainComp->loadTexture("../grass.jpg");
	TransformComponent* terrtranComp = (TransformComponent*)terrain->findComponentsByType("TransformComponent").at(0);
	terrtranComp->setPosition(glm::vec3(0, -655, -450));

	btStaticPlaneShape* planeShape = new btStaticPlaneShape(btVector3(0, 1, 0), 0);
	planeShape->setMargin(20);
	btDefaultMotionState* motionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 420, 0)));
	btRigidBody::btRigidBodyConstructionInfo rbInfo(0, motionState, planeShape);
	btRigidBody* rigidBody = new btRigidBody(rbInfo);
	btDiscreteDynamicsWorld* dynamicsWorld = hierarchy.getDynamicsWorld();

	// Add the rigid body to the dynamicsWorld
	dynamicsWorld->addRigidBody(rigidBody);


	/*
	btVector3 boxSize(1, 1, 1);
	btBoxShape* boxShape = new btBoxShape(boxSize);
	btScalar newMargin = 2.0;
	boxShape->setMargin(newMargin);
	btScalar collisionMargin = boxShape->getMargin();
	std::cout << "Collision Margin: " << collisionMargin << std::endl;

	// Set the mass of the box
	btScalar boxMass = 4.7f; // Adjust the mass as needed

	// Set the initial position and orientation of the box
	btTransform boxTransform;
	boxTransform.setIdentity(); // No initial rotation
	//boxTransform.setOrigin(btVector3(transformPos.x, transformPos.y, transformPos.z)); // Initial position
	boxTransform.setOrigin(btVector3(-25, 0, 100)); // Initial position

	// Create the motion state
	btDefaultMotionState* boxMotionState = new btDefaultMotionState(boxTransform);

	// Create the rigid body construction info
	btVector3 boxInertia(0, 0, 0);
	boxShape->calculateLocalInertia(boxMass, boxInertia);

	btRigidBody * cameraRigidBody = new btRigidBody(btRigidBody::btRigidBodyConstructionInfo(boxMass, boxMotionState, boxShape, boxInertia));;

	dynamicsWorld->addRigidBody(cameraRigidBody);
	*/
}