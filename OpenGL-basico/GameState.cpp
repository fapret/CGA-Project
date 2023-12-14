#include "GameState.h"
#include <string>
#include "Entity.h"
#include "Hierarchy.h"
#include "MeshComponent.h"
#include "TerrainComponent.h"
#include "ColliderComponent.h"

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

	std::string motelName = "Motel";
	Entity* motel = new Entity(motelName);
	hierarchy.addEntity(motel);
	MeshComponent* motelMesh = new MeshComponent();
	motel->addComponent(motelMesh);
	motelMesh->setFatherEntity(motel);
	motelMesh->importObject("../models/motel.fbx", 1000.0f);
	TransformComponent* tranMotel = (TransformComponent*)motel->findComponentsByType("TransformComponent").at(0);
	tranMotel->setPosition(glm::vec3(238, 231, -115));
	tranMotel->setScale(glm::vec3(5, 5, 5));
	tranMotel->setRotation(glm::vec3(-90, 0, 180));

	std::string discoName = "Baile";
	Entity* disco = new Entity(discoName);
	hierarchy.addEntity(disco);
	MeshComponent* discoMesh = new MeshComponent();
	disco->addComponent(discoMesh);
	discoMesh->setFatherEntity(disco);
	discoMesh->importObject("../models/nightclub.fbx", 1000.0f);
	TransformComponent* tranDisco = (TransformComponent*)disco->findComponentsByType("TransformComponent").at(0);
	tranDisco->setRotation(glm::vec3(-90, 0, 0));
	tranDisco->setPosition(glm::vec3(0, 500, 0));
	tranDisco->setScale(glm::vec3(5, 5, 5));

	std::string coneName = "cono";
	Entity* cono = new Entity(coneName);
	hierarchy.addEntity(cono);
	MeshComponent* meshCono = new MeshComponent();
	cono->addComponent(meshCono);
	ColliderComponent* colliderCompCono = new ColliderComponent();
	meshCono->setFatherEntity(cono);
	colliderCompCono->setFatherEntity(cono);
	cono->addComponent(colliderCompCono);
	meshCono->importObject("../models/cone.fbx", 2000.0f);
	TransformComponent* tranCono = (TransformComponent*)cono->findComponentsByType("TransformComponent").at(0);
	tranCono->setPosition(glm::vec3(-25, 227, -100));
	tranCono->setScale(glm::vec3(0.02, 0.02, 0.02));
	colliderCompCono->setUpCollission(0, 200, 10, false, glm::vec3(0, 0, 0));
	hierarchy.addDynamicObject(colliderCompCono);

	std::string objectName2 = "Thanos";
	Entity* object2 = new Entity(objectName2);
	hierarchy.addEntity(object2);
	MeshComponent* meshComp2 = new MeshComponent();
	object2->addComponent(meshComp2);
	ColliderComponent* colliderCompThanos = new ColliderComponent();
	meshComp2->setFatherEntity(object2);
	colliderCompThanos->setFatherEntity(object2);
	object2->addComponent(colliderCompThanos);
	meshComp2->importObject("../models/thanos.fbx", 2000.0f);
	meshComp2->addAnimation("../models/thanos.fbx");
	TransformComponent* tranCompThanos = (TransformComponent*)object2->findComponentsByType("TransformComponent").at(0);
	tranCompThanos->setPosition(glm::vec3(15, 500, 15));
	tranCompThanos->setRotation(glm::vec3(0, 45, 0));
	tranCompThanos->setScale(glm::vec3(0.2, 0.2, 0.2));
	colliderCompThanos->setUpCollission(0, 0, 4, false, glm::vec3(0, -2, 0));

	std::string stormtrooper = "StormTrooper";
	Entity* stormObj = new Entity(stormtrooper);
	hierarchy.addEntity(stormObj);
	MeshComponent* meshStorm = new MeshComponent();
	stormObj->addComponent(meshStorm);
	meshStorm->setFatherEntity(stormObj);
	meshStorm->importObject("../models/stormtropper.fbx", 2000.0f);
	meshStorm->addAnimation("../models/stormtropper.fbx");
	TransformComponent* tranCompStorm = (TransformComponent*)stormObj->findComponentsByType("TransformComponent").at(0);
	tranCompStorm->setPosition(glm::vec3(-23, 492, 5));
	tranCompStorm->setScale(glm::vec3(3, 3, 3));
	tranCompStorm->setRotation(glm::vec3(0, -45, 0));

	std::string shrekName = "Shrek";
	Entity* shrek = new Entity(shrekName);
	hierarchy.addEntity(shrek);
	MeshComponent* meshShrek = new MeshComponent();
	shrek->addComponent(meshShrek);
	meshShrek->setFatherEntity(shrek);
	meshShrek->importObject("../models/shrek.fbx", 2000.0f);
	meshShrek->addAnimation("../models/shrek.fbx");
	TransformComponent* tranCompShrek = (TransformComponent*)shrek->findComponentsByType("TransformComponent").at(0);
	tranCompShrek->setPosition(glm::vec3(0, 500, -35));
	tranCompShrek->setScale(glm::vec3(0.005, 0.005, 0.005));
	tranCompShrek->setRotation(glm::vec3(0, 180, 0));

	std::string alienName = "Alien";
	Entity* alien = new Entity(alienName);
	hierarchy.addEntity(alien);
	MeshComponent* meshAlien = new MeshComponent();
	alien->addComponent(meshAlien);
	meshAlien->setFatherEntity(alien);
	meshAlien->importObject("../models/alien.fbx", 2000.0f);
	meshAlien->addAnimation("../models/alien.fbx");
	TransformComponent* tranCompAlien = (TransformComponent*)alien->findComponentsByType("TransformComponent").at(0);
	tranCompAlien->setPosition(glm::vec3(-15, 500, 15));
	tranCompAlien->setScale(glm::vec3(0.040, 0.040, 0.040));
	tranCompAlien->setRotation(glm::vec3(0, -60, 0));

	std::string santaName = "Santa";
	Entity* santa = new Entity(santaName);
	hierarchy.addEntity(santa);
	MeshComponent* meshSanta = new MeshComponent();
	santa->addComponent(meshSanta);
	meshSanta->setFatherEntity(santa);
	meshSanta->importObject("../models/santa.fbx", 2000.0f);
	meshSanta->addAnimation("../models/santa.fbx");
	TransformComponent* tranCompSanta = (TransformComponent*)santa->findComponentsByType("TransformComponent").at(0);
	tranCompSanta->setPosition(glm::vec3(5, 492.5, -60));
	tranCompSanta->setScale(glm::vec3(0.01, 0.01, 0.01));
	tranCompSanta->setRotation(glm::vec3(0, 180, 0));

	std::string bailaName = "Bailarina";
	Entity* baila = new Entity(bailaName);
	hierarchy.addEntity(baila);
	MeshComponent* meshBaila = new MeshComponent();
	baila->addComponent(meshBaila);
	meshBaila->setFatherEntity(baila);
	meshBaila->importObject("../models/bailarina.fbx", 2000.0f);
	meshBaila->addAnimation("../models/bailarina.fbx");
	TransformComponent* tranCompBaila = (TransformComponent*)baila->findComponentsByType("TransformComponent").at(0);
	tranCompBaila->setPosition(glm::vec3(5, 500, -5));
	tranCompBaila->setScale(glm::vec3(0.06, 0.06, 0.06));
	//tranCompBaila->setRotation(glm::vec3(0, 180, 0));

	std::string baila2Name = "GreenDancer";
	Entity* baila2 = new Entity(baila2Name);
	hierarchy.addEntity(baila2);
	MeshComponent* meshBaila2 = new MeshComponent();
	baila2->addComponent(meshBaila2);
	meshBaila2->setFatherEntity(baila2);
	meshBaila2->importObject("../models/greenDancer.fbx", 2000.0f);
	meshBaila2->addAnimation("../models/greenDancer.fbx");
	TransformComponent* tranCompBaila2 = (TransformComponent*)baila2->findComponentsByType("TransformComponent").at(0);
	tranCompBaila2->setPosition(glm::vec3(0, 500, -15));
	tranCompBaila2->setScale(glm::vec3(0.06, 0.06, 0.06));
	tranCompBaila2->setRotation(glm::vec3(0, -145, 0));

	std::string skeletonName = "EsqueletoMacarena";
	Entity* macarena = new Entity(skeletonName);
	hierarchy.addEntity(macarena);
	MeshComponent* meshMacarena = new MeshComponent();
	macarena->addComponent(meshMacarena);
	meshMacarena->setFatherEntity(macarena);
	meshMacarena->importObject("../models/skeleton.fbx", 2000.0f);
	meshMacarena->addAnimation("../models/skeleton.fbx");
	TransformComponent* tranCompMaca = (TransformComponent*)macarena->findComponentsByType("TransformComponent").at(0);
	tranCompMaca->setPosition(glm::vec3(15, 500, -20));
	tranCompMaca->setScale(glm::vec3(0.110, 0.110, 0.110));
	tranCompMaca->setRotation(glm::vec3(0, 90, 0));

	std::string uruguayName = "UruguayFlag";
	Entity* uruguay = new Entity(uruguayName);
	hierarchy.addEntity(uruguay);
	MeshComponent* meshUruguay = new MeshComponent();
	uruguay->addComponent(meshUruguay);
	meshUruguay->setFatherEntity(uruguay);
	meshUruguay->importObject("../models/uruguay.fbx", 2000.0f);
	//meshUruguay->addAnimation("../models/uruguay.fbx");
	TransformComponent* tranCompUruguay = (TransformComponent*)uruguay->findComponentsByType("TransformComponent").at(0);
	//tranCompUruguay->setPosition(glm::vec3(15, 500, -20));
	//tranCompUruguay->setScale(glm::vec3(0.110, 0.110, 0.110));
	//tranCompUruguay->setRotation(glm::vec3(0, 90, 0));

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

	std::string puertaName = "Puerta";
	Entity* puerta = new Entity(puertaName);
	hierarchy.addEntity(puerta);
	ColliderComponent* colliderPuerta = new ColliderComponent();
	colliderPuerta->setFatherEntity(puerta);
	puerta->addComponent(colliderPuerta);
	TransformComponent* tranPuerta = (TransformComponent*)puerta->findComponentsByType("TransformComponent").at(0);
	tranPuerta->setPosition(glm::vec3(237, 223, -2));
	colliderPuerta->setUpCollission(0, 0, 10, false, glm::vec3(0, 0, 0));

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
