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
	this->FOV = 45.0f;
	this->ambientLight[0] = 0.2f;
	this->ambientLight[1] = 0.2f;
	this->ambientLight[2] = 0.2f;
}

CameraComponent::CameraComponent(TransformComponent* transform) : EntityComponent("CameraComponent")
{
	this->transform = transform;
	this->Speed = 0.1f;
	this->yaw = 0.0f;
	this->pitch = 0.0f;
	this->isActive = false;
	this->FOV = 45.0f;
	this->ambientLight[0] = 0.2f;
	this->ambientLight[1] = 0.2f;
	this->ambientLight[2] = 0.2f;
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

float CameraComponent::getFOV()
{
	return FOV;
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

glm::vec3 CameraComponent::getAmbientLight()
{
	return glm::vec3(ambientLight[0], ambientLight[1], ambientLight[2]);
}

void CameraComponent::setAmbientLight(glm::vec3 lightColor)
{
	this->ambientLight[0] = lightColor.x;
	this->ambientLight[1] = lightColor.y;
	this->ambientLight[2] = lightColor.z;
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

void CameraComponent::setFOV(float amount)
{
	this->FOV = amount;
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

void CameraComponent::update()
{
	glm::mat4 projectionM = glm::perspective(FOV, 4.0f / 3.0f, 1.0f, 10000.f);
	projectionM = glm::rotate(projectionM, glm::radians(pitch), glm::vec3(1.0f, 0.0f, 0.0f));
	projectionM = glm::rotate(projectionM, glm::radians(yaw), glm::vec3(0.0f, 1.0f, 0.0f));
	this->projection = projectionM;

	glm::mat4 viewM(1.0);
	this->view = glm::translate(viewM, glm::vec3(transform->getPosition().x, transform->getPosition().y, transform->getPosition().z));

}

glm::mat4 CameraComponent::getProjection()
{
	return projection;
}

glm::mat4 CameraComponent::getView()
{
	return view;
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
			CameraComponent* oldActive = (CameraComponent*)(hierarchy.getActiveCamera()->findComponentsByType("CameraComponent").at(0));
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
	ImGui::Text("FOV:");
	ImGui::SameLine();
	ImGui::InputFloat("##FOV", &FOV, 0.1f, 1.0f, "%.1f");

	ImGui::ColorPicker3("AmbientLight", ambientLight);
}
#endif