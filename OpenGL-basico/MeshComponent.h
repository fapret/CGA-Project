#pragma once
#include "EntityComponent.h"
#include <vector>
#include "Mesh.h"
#include "TransformComponent.h"
#include "Hierarchy.h"
#include "CameraComponent.h"
#include "SkyboxComponent.h"
#include "animation.h"
#include "animator.h"

struct LOD {
	std::vector<GLuint> vao;
	std::vector<Mesh*> meshData;
	float viewDistance;
	std::vector<int> faceAmount;
	std::vector<GLuint> textureIds;
	int numOfMeshes;
	std::vector<Texture> textures_loaded;
	int Level;
};

LOD createLOD(const std::string& pFile, float viewDistance);

class MeshComponent : public EntityComponent {
private:
	float maxViewDistance;
	std::vector<LOD*> LodLevels;
	TransformComponent* transform;
	float calculateDistance(const glm::vec3& point1, const glm::vec3& point2);
	Animator* animator;
public:
	MeshComponent();
	MeshComponent(float maxDistance);
	void draw(float deltaTime = 0.0f) override;
	void setMaxViewDistance(float maxView);
	void addLOD(LOD* lod);
	int getMaxViewDistance();
	void setFatherEntity(Entity* father) override;
	void addAnimation(const std::string& pFile);
	Animator* getAnimator();
	void importObject(const std::string& pFile, float viewDistance, bool createMesh);
#ifdef USE_IMGUI
	void EditorPropertyDraw() override;
#endif
};