#pragma once
#include "EntityComponent.h"
#include "TransformComponent.h"
#include "Hierarchy.h"

class CameraComponent : public EntityComponent {
private:
	float Speed;
	float yaw;
	float pitch;
	TransformComponent* transform;
	bool isActive;
public:
	CameraComponent();
	CameraComponent(TransformComponent* transform);
	float getSpeed();
	float getYaw();
	float getPitch();
	bool getIsActive();
	void setSpeed(float speed);
	void setYaw(float yaw);
	void setPitch(float pitch);
	void setIsActive(bool status);
	TransformComponent* getTransform();
#ifdef USE_IMGUI
	void EditorPropertyDraw() override;
#endif
};
