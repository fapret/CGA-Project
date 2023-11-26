#include "EntityComponent.h"
#include "GUIGenerator.h"

std::string EntityComponent::getType()
{
    return type;
}

std::string EntityComponent::getId()
{
    return id;
}

EntityComponent::EntityComponent()
{
    this->id = generateGUID();
}

EntityComponent::EntityComponent(std::string type)
{
    this->id = generateGUID();
    this->type = type;
}

#ifdef USE_IMGUI
void EntityComponent::EditorPropertyDraw()
{
}
#endif