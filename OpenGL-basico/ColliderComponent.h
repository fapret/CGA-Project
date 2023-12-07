#pragma once
#include "EntityComponent.h"

class ColliderComponent : public EntityComponent {
public:
	ColliderComponent();
	void draw(float deltaTime = 0.0f) override;
#ifdef USE_IMGUI
	void EditorPropertyDraw() override;
#endif
};