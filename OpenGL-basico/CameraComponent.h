#pragma once
#include "EntityComponent.h"
#include "TransformComponent.h"

class CameraComponent : public EntityComponent {
private:
	float Speed;
	float yaw;
	float pitch;
	TransformComponent* transform;
public:
	CameraComponent();
	CameraComponent(TransformComponent* transform);
	float getSpeed();
	float getYaw();
	float getPitch();
	void setSpeed(float speed);
	void setX(float x);
	void setZ(float z);
	void setY(float y);
	void setYaw(float yaw);
	void setPitch(float pitch);
	TransformComponent* getTransform();
#ifdef USE_IMGUI
	void EditorPropertyDraw() override;
#endif
};
