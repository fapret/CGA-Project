#pragma once
#include "EntityComponent.h"
#include <FreeImage.h>
#include <glad/glad.h>
#include <stdexcept>
#include "Hierarchy.h"
#include "CameraComponent.h"
#include "SkyboxComponent.h"
#include <btBulletDynamicsCommon.h>
#include <BulletCollision/CollisionShapes/btHeightfieldTerrainShape.h>


class TerrainComponent : public EntityComponent {
private:
	int width, height;
	float* vertices;
	unsigned int* indices;
	GLuint vao, vbo, ebo, vboNormals;
	GLuint texture; // Texture ID
	float* textureCoords;
	float* normals;
	void calculateNormal(int x, int y);
	float scale;
	float heightScale;
	TransformComponent* transform;
public:
	TerrainComponent();
	~TerrainComponent();
	void loadHeightmap(const char* filePath, float scale = 1.0f, float heightScale = 1.0f, float textureScale = 50.0f);
	void loadTexture(const char* texturePath);
	void draw(float deltaTime = 0.0f) override;
	void createPhysics();
	void setFatherEntity(Entity* father) override;
};
