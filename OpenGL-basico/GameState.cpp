#include "GameState.h"
#include <string>
#include "Entity.h"
#include "Hierarchy.h"
#include "MeshComponent.h"
#include "TerrainComponent.h"

void loadState()
{
	Hierarchy& hierarchy = Hierarchy::getInstance();
	/*
	std::string objectName = "ObjetoPrueba";
	Entity* object = new Entity(objectName);
	hierarchy.addEntity(object);
	MeshComponent* meshComp = new MeshComponent();
	object->addComponent(meshComp);
	meshComp->setFatherEntity(object);
	LOD lod0 = createLOD("../models/jugador.obj", 0.0f);
	meshComp->addLOD(lod0);
	//LOD lod1 = createLOD("../models/thanos.obj", 10.0f);
	//meshComp->addLOD(lod1);
	//LOD lod2 = createLOD("../models/sphere.obj", 20.0f);
	//meshComp->addLOD(lod2);
	*/

	std::string objectName2 = "Thanos";
	Entity* object2 = new Entity(objectName2);
	hierarchy.addEntity(object2);
	MeshComponent* meshComp2 = new MeshComponent();
	object2->addComponent(meshComp2);
	meshComp2->setFatherEntity(object2);
	//LOD lod20 = createLOD("../models/thanos.fbx", 0.0f);
	//meshComp2->addLOD(lod20);
	meshComp2->importObject("../models/thanos.fbx", 2000.0f);
	meshComp2->addAnimation("../models/thanos.fbx");

	/*std::string objectName3 = "Terrain";
	Entity* terrain = new Entity(objectName3);
	hierarchy.addEntity(terrain);
	TerrainComponent* terrainComp = new TerrainComponent();
	terrain->addComponent(terrainComp);
	terrainComp->setFatherEntity(terrain);
	terrainComp->loadHeightmap("../iceland_heightmap.png", 10.0f, 0.5f);
	terrainComp->loadTexture("../grass.jpg");
	terrainComp->createPhysics();
	*/

	btDiscreteDynamicsWorld* dynamicsWorld = hierarchy.getDynamicsWorld();
	if (!dynamicsWorld) {
		throw std::runtime_error("DynamicsWorld is not initialized.");
	}

	btVector3 boxSize(20, 20, 20);
	btBoxShape* boxShape = new btBoxShape(boxSize);
	btScalar newMargin = 10.1;
	boxShape->setMargin(newMargin);
	btScalar collisionMargin = boxShape->getMargin();
	std::cout << "Collision Margin: " << collisionMargin << std::endl;

	// Set the mass of the box
	btScalar boxMass = 10.0; // Adjust the mass as needed

	// Set the initial position and orientation of the box
	btTransform boxTransform;
	boxTransform.setIdentity(); // No initial rotation
	//boxTransform.setOrigin(btVector3(transformPos.x, transformPos.y, transformPos.z)); // Initial position
	boxTransform.setOrigin(btVector3(0, 0, 100)); // Initial position


	// Create the motion state
	btDefaultMotionState* boxMotionState = new btDefaultMotionState(boxTransform);

	// Create the rigid body construction info
	btVector3 boxInertia(0, 0, 0);
	boxShape->calculateLocalInertia(boxMass, boxInertia);

	btRigidBody * box = new btRigidBody(btRigidBody::btRigidBodyConstructionInfo(boxMass, boxMotionState, boxShape, boxInertia));;

	dynamicsWorld->addRigidBody(box);
	/*
	// Create a static terrain shape
	btScalar newMargin = 10.1;
	btStaticPlaneShape* planeShape = new btStaticPlaneShape(btVector3(0, 1, 0), 0);
	planeShape->setMargin(newMargin);
	btDefaultMotionState* motionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 300, 0)));
	btRigidBody::btRigidBodyConstructionInfo rbInfo(0, motionState, planeShape);
	btRigidBody* rigidBody = new btRigidBody(rbInfo);

	// Add the rigid body to the dynamicsWorld
	dynamicsWorld->addRigidBody(rigidBody);
	*/
}
