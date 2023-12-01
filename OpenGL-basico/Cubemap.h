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

class Cubemap {
private:
	GLuint textureId;
	GLuint skyboxVAO, skyboxVBO;
public:
	Cubemap();
	GLuint loadCubemap(std::vector<const char*> faces);
	void draw();
};