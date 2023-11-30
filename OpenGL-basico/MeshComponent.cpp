#include "MeshComponent.h"

float MeshComponent::calculateDistance(const glm::vec3& point1, const glm::vec3& point2)
{
	float distance = glm::sqrt(glm::pow(point2.x - point1.x, 2) +
		glm::pow(point2.y - point1.y, 2) +
		glm::pow(point2.z - point1.z, 2));
	return distance;
}

MeshComponent::MeshComponent() : EntityComponent("MeshComponent")
{
	this->maxViewDistance = 10000.0f;
	this->transform = new TransformComponent();
}

MeshComponent::MeshComponent(float maxDistance) : EntityComponent("MeshComponent")
{
	this->maxViewDistance = maxDistance;
	this->transform = new TransformComponent();
}

void MeshComponent::draw()
{
	Hierarchy& hierarchy = Hierarchy::getInstance();
	Entity* camEntity = hierarchy.getActiveCamera();
	if (camEntity != nullptr) {
		std::vector<EntityComponent*> camTransformList = camEntity->findComponentsByType("TransformComponent");
		if (camTransformList.empty()) {
			return;
		}
		TransformComponent* camTransform = (TransformComponent*)camTransformList.at(0);
		float distance = calculateDistance(camTransform->getPosition(), transform->getPosition());

		// Find the appropriate LOD level based on distance
		LOD* selectedLOD = nullptr;
		float minDistanceDifference = std::numeric_limits<float>::max();

		for (auto& lod : LodLevels) {
			float distanceDifference = std::abs(distance - lod.viewDistance);
			if (distanceDifference < minDistanceDifference) {
				minDistanceDifference = distanceDifference;
				selectedLOD = &lod;
			}
		}

		if (selectedLOD) {
			RenderMultipleMeshVAO(selectedLOD->vao, selectedLOD->faceAmount, selectedLOD->textureIds);
		}

	}
}

void MeshComponent::setMaxViewDistance(float maxView)
{
	this->maxViewDistance = maxView;
}

void MeshComponent::addLOD(LOD lod)
{
	this->LodLevels.push_back(lod);
}

int MeshComponent::getMaxViewDistance()
{
	return maxViewDistance;
}

void MeshComponent::setFatherEntity(Entity* father)
{
	EntityComponent::setFatherEntity(father);
	std::vector<EntityComponent*> transformList = father->findComponentsByType("TransformComponent");
	if (transformList.size() == 0) {
		father->addComponent(transform);
	}
}

#ifdef USE_IMGUI
void MeshComponent::EditorPropertyDraw()
{
	EntityComponent::EditorPropertyDraw();
}
#endif