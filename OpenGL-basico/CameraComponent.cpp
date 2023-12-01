#include "CameraComponent.h"

float CameraComponent::wrapAngle(float angle)
{
	constexpr float TwoPi = 2.0f * glm::pi<float>();
	while (angle < -glm::pi<float>()) {
		angle += TwoPi;
	}
	while (angle > glm::pi<float>()) {
		angle -= TwoPi;
	}
	return angle;
}

CameraComponent::CameraComponent() : EntityComponent("CameraComponent")
{
	this->transform = new TransformComponent();
	this->Speed = 70.1f;
	this->yaw = 0.0f;
	this->pitch = 0.0f;
	this->isActive = false;
}

CameraComponent::CameraComponent(TransformComponent* transform) : EntityComponent("CameraComponent")
{
	this->transform = transform;
	this->Speed = 0.1f;
	this->yaw = 0.0f;
	this->pitch = 0.0f;
	this->isActive = false;
}

float CameraComponent::getSpeed()
{
	return Speed;
}

float CameraComponent::getYaw()
{
	return yaw;
}

float CameraComponent::getPitch()
{
	return pitch;
}

glm::vec3 CameraComponent::getViewDirection()
{

	float yawRad = glm::radians(yaw);
	float pitchRad = glm::radians(pitch);

	// Calculate the view direction
	float x = glm::cos(yawRad) * glm::cos(pitchRad);
	float y = glm::sin(pitchRad);
	float z = glm::sin(yawRad) * glm::cos(pitchRad);

	return glm::normalize(glm::vec3(x, y, z));
}

bool CameraComponent::getIsActive()
{
	return isActive;
}

void CameraComponent::setSpeed(float speed)
{
	this->Speed = speed;
}

void CameraComponent::setYaw(float yaw)
{
	this->yaw = glm::degrees(wrapAngle(glm::radians(yaw)));
}

void CameraComponent::setPitch(float pitch)
{
	this->pitch = pitch;
}

void CameraComponent::setIsActive(bool status)
{
	this->isActive = status;
}

TransformComponent* CameraComponent::getTransform()
{
	return transform;
}

void CameraComponent::draw()
{
}

void CameraComponent::setFatherEntity(Entity* father)
{
	EntityComponent::setFatherEntity(father);
	std::vector<EntityComponent*> transformList = father->findComponentsByType("TransformComponent");
	if (transformList.size() == 0) {
		father->addComponent(transform);
	}
}

#ifdef USE_IMGUI
void CameraComponent::EditorPropertyDraw()
{
	EntityComponent::EditorPropertyDraw();
	ImGui::Text("Is Active Camera: %s", isActive ? "True" : "False");
	if (getFatherEntity() != nullptr && !isActive && ImGui::Button("Set Camera as active")) {
		// Code to execute when the button is pressed
		Hierarchy& hierarchy = Hierarchy::getInstance();
		if (hierarchy.getActiveCamera() != nullptr) {
			CameraComponent* oldActive = (CameraComponent*) (hierarchy.getActiveCamera()->findComponentsByType("CameraComponent").at(0));
			oldActive->setIsActive(false);
		}
		this->isActive = true;
		hierarchy.setActiveCamera(getFatherEntity());
	}
	ImGui::Text("Speed:");
	ImGui::SameLine();
	ImGui::InputFloat("##Speed", &Speed, 0.01f, 0.1f, "%.3f");
	ImGui::Text("Yaw:");
	ImGui::SameLine();
	ImGui::InputFloat("##Yaw", &yaw, 0.01f, 0.1f, "%.3f");
	ImGui::Text("Pitch:");
	ImGui::SameLine();
	ImGui::InputFloat("##Pitch", &pitch, 0.01f, 0.1f, "%.3f");
}
#endif
