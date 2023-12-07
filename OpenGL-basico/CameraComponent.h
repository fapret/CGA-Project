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
	float FOV;
	glm::mat4 projection;
	glm::mat4 view;
	float ambientLight[3];
	btRigidBody* cameraRigidBody;
public:
	CameraComponent();
	CameraComponent(TransformComponent* transform);
	float getSpeed();
	float getYaw();
	float getPitch();
	float getFOV();
	glm::vec3 getViewDirection();
	glm::vec3 getAmbientLight();
	void setAmbientLight(glm::vec3 lightColor);
	bool getIsActive();
	void setSpeed(float speed);
	void setYaw(float yaw);
	void setPitch(float pitch);
	void setIsActive(bool status);
	void setFOV(float amount);
	TransformComponent* getTransform();
	void draw() override;
	void setFatherEntity(Entity* father) override;
	void update();
	glm::mat4 getProjection();
	glm::mat4 getView();
	void setUpCollission();
	void updateRigidBody();
	void checkCollision();
#ifdef USE_IMGUI
	void EditorPropertyDraw() override;
#endif
};