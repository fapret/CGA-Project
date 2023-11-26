#pragma once
#include "EntityComponent.h"
#include "Vector3.h"

class TransformComponent : public EntityComponent {
private:
	Vector3* position;
	Vector3* scale;
	Vector3* rotation;
public:
	Vector3* getPosition();
	void setPosition(Vector3* pos);
	Vector3* getScale();
	void setScale(Vector3* scale);
	Vector3* getRotation();
	void setRotation(Vector3* rot);
	TransformComponent();
#ifdef USE_IMGUI
	void EditorPropertyDraw() override;
#endif
};