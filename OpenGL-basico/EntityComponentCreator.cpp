#include "EntityComponentCreator.h"

EntityComponentCreator::EntityComponentCreator() : componentNames{ "CameraComponent", "TransformComponent", "ColliderComponent", "MeshComponent", "LightComponent", "TerrainComponent"}, componentNamesSize(6)
{
}

EntityComponentCreator& EntityComponentCreator::getInstance()
{
	static EntityComponentCreator instance;  // This line ensures that the instance is created once
	return instance;
}

EntityComponent* EntityComponentCreator::createComponent(int index) {
	switch (index)
	{
	case 0:
		return new CameraComponent();
		break;
	case 1:
		return new TransformComponent();
		break;
	case 2:
		return new ColliderComponent();
		break;
	case 3:
		return new MeshComponent();
		break;
	case 4:
		return new LightComponent();
		break;
	case 5:
		return new TerrainComponent();
		break;
	default:
		return new EntityComponent();
		break;
	}
}