#pragma once
#include "EntityComponent.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class TransformComponent : public EntityComponent {
private:
	glm::vec3 position;
	glm::vec3 scale;
	glm::vec3 rotation;
	glm::vec3 velocity;
public:
	glm::vec3 getPosition();
	void setPosition(glm::vec3 pos);
	glm::vec3 getVelocity();
	void setVelocity(glm::vec3 vel);
	glm::vec3 getScale();
	void setScale(glm::vec3 scale);
	glm::vec3 getRotation();
	void setRotation(glm::vec3 rot);
	TransformComponent();
#ifdef USE_IMGUI
	void EditorPropertyDraw() override;
#endif
};