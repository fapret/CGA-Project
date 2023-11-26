#include "CameraComponent.h"

CameraComponent::CameraComponent() : EntityComponent("CameraComponent")
{
	this->transform = new TransformComponent();
	this->Speed = 0.1f;
	this->X = 0.0f;
	this->Z = -4.0f;
	this->yaw = 0.0f;
	this->pitch = 0.0f;
}

CameraComponent::CameraComponent(TransformComponent* transform) : EntityComponent("CameraComponent")
{
	this->transform = transform;
	this->Speed = 0.1f;
	this->X = 0.0f;
	this->Z = -4.0f;
	this->yaw = 0.0f;
	this->pitch = 0.0f;
}

float CameraComponent::getSpeed()
{
	return Speed;
}

float CameraComponent::getX()
{
	return X;
}

float CameraComponent::getZ()
{
	return Z;
}

float CameraComponent::getY()
{
	return Y;
}

float CameraComponent::getYaw()
{
	return yaw;
}

float CameraComponent::getPitch()
{
	return pitch;
}

void CameraComponent::setSpeed(float speed)
{
	this->Speed = speed;
}

void CameraComponent::setX(float x)
{
	this->X = x;
}

void CameraComponent::setZ(float z)
{
	this->Z = z;
}

void CameraComponent::setY(float y)
{
	this->Y = y;
}

void CameraComponent::setYaw(float yaw)
{
	this->yaw = yaw;
}

void CameraComponent::setPitch(float pitch)
{
	this->pitch = pitch;
}

TransformComponent* CameraComponent::getTransform()
{
	return transform;
}

#ifdef USE_IMGUI
void CameraComponent::EditorPropertyDraw()
{
	ImGui::Text("Speed:");
	ImGui::SameLine();
	ImGui::InputFloat("##Speed", &Speed, 0.01f, 0.1f, "%.3f");
	ImGui::Text("X:");
	ImGui::SameLine();
	ImGui::InputFloat("##X", &X, 0.01f, 0.1f, "%.3f");
	ImGui::Text("Z:");
	ImGui::SameLine();
	ImGui::InputFloat("##Z", &Z, 0.01f, 0.1f, "%.3f");
	ImGui::Text("Yaw:");
	ImGui::SameLine();
	ImGui::InputFloat("##Yaw", &yaw, 0.01f, 0.1f, "%.3f");
	ImGui::Text("Pitch:");
	ImGui::SameLine();
	ImGui::InputFloat("##Pitch", &pitch, 0.01f, 0.1f, "%.3f");
}
#endif