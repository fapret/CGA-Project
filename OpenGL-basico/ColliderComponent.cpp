#include "ColliderComponent.h"

ColliderComponent::ColliderComponent() : EntityComponent("ColliderComponent")
{
}

void ColliderComponent::draw()
{
}

#ifdef USE_IMGUI
void ColliderComponent::EditorPropertyDraw()
{
	EntityComponent::EditorPropertyDraw();
}
#endif
