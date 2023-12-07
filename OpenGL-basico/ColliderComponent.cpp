#include "ColliderComponent.h"

ColliderComponent::ColliderComponent() : EntityComponent("ColliderComponent")
{
}

void ColliderComponent::draw(float deltaTime)
{
}

#ifdef USE_IMGUI
void ColliderComponent::EditorPropertyDraw()
{
	EntityComponent::EditorPropertyDraw();
}
#endif
