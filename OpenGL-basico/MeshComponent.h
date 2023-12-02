#pragma once
#include "EntityComponent.h"
#include <vector>
#include "Mesh.h"
#include "TransformComponent.h"
#include "Hierarchy.h"
#include "CameraComponent.h"

struct LOD {
	std::vector<GLuint> vao;
	std::vector<Mesh*> meshData;
	float viewDistance;
	std::vector<int> faceAmount;
	std::vector<GLuint> textureIds;
	int numOfMeshes;
};

LOD createLOD(const std::string& pFile, float viewDistance);

class MeshComponent : public EntityComponent {
private:
	float maxViewDistance;
	std::vector<LOD> LodLevels;
	TransformComponent* transform;
	float calculateDistance(const glm::vec3& point1, const glm::vec3& point2);
public:
	MeshComponent();
	MeshComponent(float maxDistance);
	void draw() override;
	void setMaxViewDistance(float maxView);
	void addLOD(LOD lod);
	int getMaxViewDistance();
	void setFatherEntity(Entity* father) override;
#ifdef USE_IMGUI
	void EditorPropertyDraw() override;
#endif
};