#pragma once
#include "EntityComponent.h"

class ColliderComponent : public EntityComponent {
public:
	ColliderComponent();
	void draw() override;
#ifdef USE_IMGUI
	void EditorPropertyDraw() override;
#endif
};