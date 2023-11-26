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

void EntityComponent::draw()
{
}

#ifdef USE_IMGUI
void EntityComponent::EditorPropertyDraw()
{
    //Util para debugear, muestra los guid de todos los componentes
    //ImGui::Text("GUID:");
    //ImGui::SameLine();
    //ImGui::Text(this->id.c_str());
    //ImGui::Separator();
}
#endif