#include "EntityComponentCreator.h"

EntityComponentCreator::EntityComponentCreator() : componentNames{ "CameraComponent", "TransformComponent", "ColliderComponent", "MeshComponent" }, componentNamesSize(4)
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
	default:
		return new EntityComponent();
		break;
	}
}