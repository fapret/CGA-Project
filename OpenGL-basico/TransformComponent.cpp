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
