#pragma once
#include "EntityComponent.h"
#include "TransformComponent.h"
#include "Hierarchy.h"

class LightComponent : public EntityComponent {
protected:
	float LightColor[3];
	TransformComponent* transform;
	float localPos[3];
	float yaw;
	float pitch;
public:
	LightComponent();
	void draw(float deltaTime = 0.0f) override;
	glm::vec3 getLightColor();
	void setLightColor(glm::vec3 lightColor);
	float getYaw();
	float getPitch();
	void setYaw(float yaw);
	void setPitch(float pitch);
	glm::vec3 getLocalPos();
	void setLocalPos(glm::vec3 pos);
	void setFatherEntity(Entity* father) override;
#ifdef USE_IMGUI
	void EditorPropertyDraw() override;
#endif
};