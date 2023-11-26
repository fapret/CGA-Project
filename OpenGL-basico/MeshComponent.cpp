#include "MeshComponent.h"

MeshComponent::MeshComponent() : EntityComponent("MeshComponent")
{
}

void MeshComponent::draw()
{
}

void MeshComponent::EditorPropertyDraw()
{
	EntityComponent::EditorPropertyDraw();
}
