#include "GameState.h"
#include <string>
#include "Entity.h"
#include "Hierarchy.h"
#include "MeshComponent.h"
#include "TerrainComponent.h"

void loadState()
{
	Hierarchy& hierarchy = Hierarchy::getInstance();
	std::string objectName = "ObjetoPrueba";
	Entity* object = new Entity(objectName);
	hierarchy.addEntity(object);
	MeshComponent* meshComp = new MeshComponent();
	object->addComponent(meshComp);
	meshComp->setFatherEntity(object);
	LOD lod0 = createLOD("../models/jugador.obj", 0.0f);
	meshComp->addLOD(lod0);
	LOD lod1 = createLOD("../models/cube.obj", 10.0f);
	meshComp->addLOD(lod1);
	LOD lod2 = createLOD("../models/sphere.obj", 20.0f);
	meshComp->addLOD(lod2);

	/*
	std::string objectName2 = "ObjetoPrueba2";
	Entity* object2 = new Entity(objectName2);
	hierarchy.addEntity(object2);
	MeshComponent* meshComp2 = new MeshComponent();
	object2->addComponent(meshComp2);
	meshComp2->setFatherEntity(object2);
	//LOD lod20 = createLOD("../models/uploads_files_2720101_BusGameMap.obj", 0.0f);
	//meshComp2->addLOD(lod20);
	//LOD lod21 = createLOD("../models/OC56_MelaleucaAlternifolia_OBJ/OBJ_OC56_MelaleucaAlternifolia_2.obj", 200.0f);
	//meshComp2->addLOD(lod21);
	*/

	std::string objectName3 = "Terrain";
	Entity* terrain = new Entity(objectName3);
	hierarchy.addEntity(terrain);
	TerrainComponent* terrainComp = new TerrainComponent();
	terrain->addComponent(terrainComp);
	terrainComp->setFatherEntity(terrain);
	terrainComp->loadHeightmap("../island_heightmap.png", 10.0f, 0.1f);
	terrainComp->loadTexture("../grass.jpg");
}
