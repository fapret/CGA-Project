#pragma once
#include "EntityComponent.h"

class MeshComponent : public EntityComponent {
public:
	MeshComponent();
	void draw() override;
#ifdef USE_IMGUI
	void EditorPropertyDraw() override;
#endif
};