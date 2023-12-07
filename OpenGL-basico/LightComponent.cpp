#include "LightComponent.h"

LightComponent::LightComponent() : EntityComponent("LightComponent")
{
	this->transform = new TransformComponent();
}

void LightComponent::draw(float deltaTime)
{
}

glm::vec3 LightComponent::getLightColor()
{
    return glm::vec3(LightColor[0], LightColor[1], LightColor[2]);
}

void LightComponent::setLightColor(glm::vec3 lightColor)
{
	this->LightColor[0] = lightColor.x;
	this->LightColor[1] = lightColor.y;
	this->LightColor[2] = lightColor.z;
}

float LightComponent::getYaw()
{
	return yaw;
}

float LightComponent::getPitch()
{
	return pitch;
}

void LightComponent::setYaw(float yaw)
{
	this->yaw = yaw;
}

void LightComponent::setPitch(float pitch)
{
	this->pitch = pitch;
}

glm::vec3 LightComponent::getLocalPos()
{
	return glm::vec3(localPos[0], localPos[1], localPos[2]);
}

void LightComponent::setLocalPos(glm::vec3 pos)
{
	this->localPos[0] = pos.x;
	this->localPos[1] = pos.y;
	this->localPos[2] = pos.z;
}

void LightComponent::setFatherEntity(Entity* father)
{
	EntityComponent::setFatherEntity(father);
	std::vector<EntityComponent*> transformList = father->findComponentsByType("TransformComponent");
	if (transformList.size() == 0) {
		father->addComponent(transform);
	}
}

#ifdef USE_IMGUI
void LightComponent::EditorPropertyDraw()
{
}
#endif // DEBUG
