#include "TransformComponent.h"

Vector3* TransformComponent::getPosition()
{
    return position;
}

void TransformComponent::setPosition(Vector3* pos)
{
    this->position = pos;
}

Vector3* TransformComponent::getScale()
{
    return scale;
}

void TransformComponent::setScale(Vector3* scale)
{
    this->scale = scale;
}

Vector3* TransformComponent::getRotation()
{
    return rotation;
}

void TransformComponent::setRotation(Vector3* rot)
{
    this->rotation = rot;
}

TransformComponent::TransformComponent() : EntityComponent("TransformComponent")
{
    this->position = new Vector3();
    this->rotation = new Vector3();
    this->scale = new Vector3(1.0f,1.0f,1.0f);
}

#ifdef USE_IMGUI
void TransformComponent::EditorPropertyDraw()
{
    EntityComponent::EditorPropertyDraw();
    float xValue = this->position->getX();
    float yValue = this->position->getY();
    float zValue = this->position->getZ();
    ImGui::Text("Position");
    ImGui::Separator();
    ImGui::Text("X:");
    ImGui::SameLine();
    ImGui::InputFloat("##X", &xValue, 0.01f, 0.1f, "%.3f");
    ImGui::Text("Y:");
    ImGui::SameLine();
    ImGui::InputFloat("##Y", &yValue, 0.01f, 0.1f, "%.3f");
    ImGui::Text("Z:");
    ImGui::SameLine();
    ImGui::InputFloat("##Z", &zValue, 0.01f, 0.1f, "%.3f");

    float xValue2 = this->rotation->getX();
    float yValue2 = this->rotation->getY();
    float zValue2 = this->rotation->getZ();
    ImGui::Separator();
    ImGui::Text("Rotation");
    ImGui::Separator();
    ImGui::Text("X:");
    ImGui::SameLine();
    ImGui::InputFloat("##X", &xValue2, 0.01f, 0.1f, "%.3f");
    ImGui::Text("Y:");
    ImGui::SameLine();
    ImGui::InputFloat("##Y", &yValue2, 0.01f, 0.1f, "%.3f");
    ImGui::Text("Z:");
    ImGui::SameLine();
    ImGui::InputFloat("##Z", &zValue2, 0.01f, 0.1f, "%.3f");

    float xValue3 = this->scale->getX();
    float yValue3 = this->scale->getY();
    float zValue3 = this->scale->getZ();
    ImGui::Separator();
    ImGui::Text("Scale");
    ImGui::Separator();
    ImGui::Text("X:");
    ImGui::SameLine();
    ImGui::InputFloat("##X", &xValue3, 0.01f, 0.1f, "%.3f");
    ImGui::Text("Y:");
    ImGui::SameLine();
    ImGui::InputFloat("##Y", &yValue3, 0.01f, 0.1f, "%.3f");
    ImGui::Text("Z:");
    ImGui::SameLine();
    ImGui::InputFloat("##Z", &zValue3, 0.01f, 0.1f, "%.3f");
}
#endif