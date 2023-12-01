#pragma once
#include "TransformComponent.h"
#include "CameraComponent.h"
#include "ColliderComponent.h"
#include "MeshComponent.h"
#include "LightComponent.h"

class EntityComponentCreator {
private:
	EntityComponentCreator();
public:
	static EntityComponentCreator& getInstance();
	EntityComponentCreator(const EntityComponentCreator&) = delete;
	EntityComponentCreator& operator=(const EntityComponentCreator&) = delete;
	EntityComponent* createComponent(int index);
	const char* componentNames[5];
	const int componentNamesSize;
};