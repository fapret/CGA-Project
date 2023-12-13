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
	meshComp2->setFatherEntity(object2);
	meshComp2->importObject("../models/thanos.fbx", 2000.0f);
	meshComp2->addAnimation("../models/thanos.fbx");

	
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
}
