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
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(transform->getPosition().x, transform->getPosition().y, transform->getPosition().z));
			model = glm::rotate(model, glm::radians(transform->getRotation().x), glm::vec3(1.0f, 0.0f, 0.0f)); // Rotate around X axis
			model = glm::rotate(model, glm::radians(transform->getRotation().y), glm::vec3(0.0f, 1.0f, 0.0f)); // Rotate around Y axis
			model = glm::rotate(model, glm::radians(transform->getRotation().z), glm::vec3(0.0f, 0.0f, 1.0f)); // Rotate around Z axis
			model = glm::scale(model, glm::vec3(transform->getScale().x, transform->getScale().y, transform->getScale().z));
			int modelIndex = glGetUniformLocation(hierarchy.getShaders()[0], "model");
			glUniformMatrix4fv(modelIndex, 1, GL_FALSE, glm::value_ptr(model));
			RenderMultipleMeshVAO(selectedLOD->vao, selectedLOD->faceAmount, selectedLOD->textureIds);
		}
		glm::mat4 model = glm::mat4(1.0f);
		int modelIndex = glGetUniformLocation(hierarchy.getShaders()[0], "model");
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

LOD createLOD(const std::string& pFile, float viewDistance)
{
	LOD lod;
	lod.meshData = LoadMeshData(pFile);
	lod.viewDistance = viewDistance;
	for (int i = 0; i < lod.meshData.size(); i++) {
		lod.textureIds.push_back(lod.meshData[i].textureId);
	}
	for (const auto& mesh : lod.meshData) {
		lod.faceAmount.push_back(mesh.vertices.size());
	}
	lod.vao = CreateMultipleMeshVAO(lod.meshData);
	return LOD();
}
