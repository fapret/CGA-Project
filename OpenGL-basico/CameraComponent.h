#pragma once
#include "EntityComponent.h"
#include "TransformComponent.h"
#include "Hierarchy.h"
#include <SDL_stdinc.h>

class CameraComponent : public EntityComponent {
private:
	float Speed;
	float yaw;
	float pitch;
	TransformComponent* transform;
	bool isActive;
	float wrapAngle(float angle);
public:
	CameraComponent();
	CameraComponent(TransformComponent* transform);
	float getSpeed();
	float getYaw();
	float getPitch();
	glm::vec3 getViewDirection();
	bool getIsActive();
	void setSpeed(float speed);
	void setYaw(float yaw);
	void setPitch(float pitch);
	void setIsActive(bool status);
	TransformComponent* getTransform();
	void draw() override;
	void setFatherEntity(Entity* father) override;
#ifdef USE_IMGUI
	void EditorPropertyDraw() override;
#endif
};
