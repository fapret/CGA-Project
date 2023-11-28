#include "TransformComponent.h"

glm::vec3 TransformComponent::getPosition()
{
    return position;
}

void TransformComponent::setPosition(glm::vec3 pos)
{
    this->position = pos;
}

glm::vec3 TransformComponent::getVelocity()
{
    return velocity;
}

void TransformComponent::setVelocity(glm::vec3 vel)
{
    this->velocity = vel;
}

glm::vec3 TransformComponent::getScale()
{
    return scale;
}

void TransformComponent::setScale(glm::vec3 scale)
{
    this->scale = scale;
}

glm::vec3 TransformComponent::getRotation()
{
    return rotation;
}

void TransformComponent::setRotation(glm::vec3 rot)
{
    this->rotation = rot;
}

TransformComponent::TransformComponent() : EntityComponent("TransformComponent")
{
    this->position = glm::vec3();
    this->rotation = glm::vec3();
    this->scale = glm::vec3(1.0f,1.0f,1.0f);
    this->velocity = glm::vec3(0.0f, 0.0f, 0.0f);
}

#ifdef USE_IMGUI
void TransformComponent::EditorPropertyDraw()
{
    EntityComponent::EditorPropertyDraw();
    float xValue = this->position.x;
    float yValue = this->position.y;
    float zValue = this->position.z;
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

    float xValue2 = this->rotation.x;
    float yValue2 = this->rotation.y;
    float zValue2 = this->rotation.z;
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

    float xValue3 = this->scale.x;
    float yValue3 = this->scale.y;
    float zValue3 = this->scale.z;
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

    float xValue4 = this->velocity.x;
    float yValue4 = this->velocity.y;
    float zValue4 = this->velocity.z;
    ImGui::Separator();
    ImGui::Text("Velocity");
    ImGui::Separator();
    ImGui::Text("X:");
    ImGui::SameLine();
    ImGui::InputFloat("##X", &xValue4, 0.01f, 0.1f, "%.3f");
    ImGui::Text("Y:");
    ImGui::SameLine();
    ImGui::InputFloat("##Y", &yValue4, 0.01f, 0.1f, "%.3f");
    ImGui::Text("Z:");
    ImGui::SameLine();
    ImGui::InputFloat("##Z", &zValue4, 0.01f, 0.1f, "%.3f");
}
#endif