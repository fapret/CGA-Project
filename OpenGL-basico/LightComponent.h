#pragma once
#include "EntityComponent.h"

class LightComponent : public EntityComponent {
public:
	LightComponent();
	void draw() override;
#ifdef USE_IMGUI
	void EditorPropertyDraw() override;
#endif
};