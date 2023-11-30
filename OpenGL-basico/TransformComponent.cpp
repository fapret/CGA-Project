#include "TransformComponent.h"

glm::vec3 TransformComponent::getPosition()
{
    return glm::vec3(posX, posY, posZ);
}

void TransformComponent::setPosition(glm::vec3 pos)
{
    this->posX = pos.x;
    this->posY = pos.y;
    this->posZ = pos.z;
}

glm::vec3 TransformComponent::getScale()
{
    return glm::vec3(scaleX, scaleY, scaleZ);
}

void TransformComponent::setScale(glm::vec3 scale)
{
    this->scaleX = scale.x;
    this->scaleY = scale.y;
    this->scaleZ = scale.z;
}

glm::vec3 TransformComponent::getRotation()
{
    return glm::vec3(rotationX, rotationY, rotationZ);
}

void TransformComponent::setRotation(glm::vec3 rot)
{
    this->rotationX = rot.x;
    this->rotationY = rot.y;
    this->rotationZ = rot.z;
}

TransformComponent::TransformComponent() : EntityComponent("TransformComponent")
{
    this->posX = 0;
    this->posY = 0;
    this->posZ = 0;
    this->rotationX = 0;
    this->rotationY = 0;
    this->rotationZ = 0;
    this->scaleX = 1.0f;
    this->scaleY = 1.0f;
    this->scaleZ = 1.0f;
}

void TransformComponent::draw()
{
}

#ifdef USE_IMGUI
void TransformComponent::EditorPropertyDraw()
{
    EntityComponent::EditorPropertyDraw();
    ImGui::Text("Position");
    ImGui::Separator();
    ImGui::Text("X:");
    ImGui::SameLine();
    ImGui::InputFloat("##X", &posX, 0.01f, 0.1f, "%.3f");
    ImGui::Text("Y:");
    ImGui::SameLine();
    ImGui::InputFloat("##Y", &posY, 0.01f, 0.1f, "%.3f");
    ImGui::Text("Z:");
    ImGui::SameLine();
    ImGui::InputFloat("##Z", &posZ, 0.01f, 0.1f, "%.3f");

    ImGui::Separator();
    ImGui::Text("Rotation");
    ImGui::Separator();
    ImGui::Text("X:");
    ImGui::SameLine();
    ImGui::InputFloat("##RX", &rotationX, 0.01f, 0.1f, "%.3f");
    ImGui::Text("Y:");
    ImGui::SameLine();
    ImGui::InputFloat("##RY", &rotationY, 0.01f, 0.1f, "%.3f");
    ImGui::Text("Z:");
    ImGui::SameLine();
    ImGui::InputFloat("##RZ", &rotationZ, 0.01f, 0.1f, "%.3f");

    ImGui::Separator();
    ImGui::Text("Scale");
    ImGui::Separator();
    ImGui::Text("X:");
    ImGui::SameLine();
    ImGui::InputFloat("##SX", &scaleX, 0.01f, 0.1f, "%.3f");
    ImGui::Text("Y:");
    ImGui::SameLine();
    ImGui::InputFloat("##SY", &scaleY, 0.01f, 0.1f, "%.3f");
    ImGui::Text("Z:");
    ImGui::SameLine();
    ImGui::InputFloat("##SZ", &scaleZ, 0.01f, 0.1f, "%.3f");
}
#endif