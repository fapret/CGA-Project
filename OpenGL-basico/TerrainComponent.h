#pragma once
#include "EntityComponent.h"
#include <FreeImage.h>
#include <glad/glad.h>
#include <stdexcept>
#include "Hierarchy.h"
#include "CameraComponent.h"
#include "SkyboxComponent.h"

class TerrainComponent : public EntityComponent {
private:
	int width, height;
	float* vertices;
	unsigned int* indices;
	GLuint vao, vbo, ebo;
	GLuint texture; // Texture ID
	float* textureCoords;
public:
	TerrainComponent();
	~TerrainComponent();
	void loadHeightmap(const char* filePath, float scale = 1.0f, float heightScale = 1.0f);
	void loadTexture(const char* texturePath);
	void draw() override;
};