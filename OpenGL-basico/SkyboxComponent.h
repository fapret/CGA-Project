#pragma once
#include <glad/glad.h>
#include <vector>
#include <string>
#include "FreeImage.h"
#include <iostream>
#include "Hierarchy.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "CameraComponent.h"
#include "EntityComponent.h"

class SkyboxComponent : public EntityComponent {
private:
	GLuint textureId;
	GLuint skyboxVAO, skyboxVBO;
	float sunDir[3];
	float sunColor[3];
public:
	SkyboxComponent();
	GLuint loadCubemap(std::vector<const char*> faces);
	void update();
	void setSunColor(glm::vec3 color);
	glm::vec3 getSunColor();
	void setSunDirection(glm::vec3 dir);
	glm::vec3 getSunDirection();
#ifdef USE_IMGUI
	void EditorPropertyDraw() override;
#endif
};