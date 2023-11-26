#include "MeshComponent.h"

MeshComponent::MeshComponent() : EntityComponent("MeshComponent")
{
}

void MeshComponent::draw()
{
}

#ifdef USE_IMGUI
void MeshComponent::EditorPropertyDraw()
{
	EntityComponent::EditorPropertyDraw();
}
#endif