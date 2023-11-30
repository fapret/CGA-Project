#pragma once
#include "EntityComponent.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class TransformComponent : public EntityComponent {
private:
	float posX;
	float posY;
	float posZ;
	float scaleX;
	float scaleY;
	float scaleZ;
	float rotationX;
	float rotationY;
	float rotationZ;
public:
	glm::vec3 getPosition();
	void setPosition(glm::vec3 pos);
	glm::vec3 getScale();
	void setScale(glm::vec3 scale);
	glm::vec3 getRotation();
	void setRotation(glm::vec3 rot);
	TransformComponent();
	void draw() override;
#ifdef USE_IMGUI
	void EditorPropertyDraw() override;
#endif
};