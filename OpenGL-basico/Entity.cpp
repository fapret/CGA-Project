#include "Entity.h"
#include "GUIGenerator.h"

std::string Entity::getName()
{
	return name;
}

void Entity::setName(std::string name)
{
	this->name = name;
}

std::string Entity::getId()
{
	return id;
}

Entity::Entity()
{
	std::string guid = generateGUID();
	this->id = guid;
	this->name = guid;
}

Entity::Entity(std::string name)
{
	std::string guid = generateGUID();
	this->id = guid;
	this->name = name;
}

Entity::Entity(std::string name, std::string id)
{
	this->id = id;
	this->name = name;
}

Entity::~Entity()
{
	components.clear();
}

EntityComponent* Entity::findComponentByID(std::string id)
{
	for (auto& component : components) {
		if (component->getId() == id) {
			return component;
		}
	}
	return nullptr;
}

std::vector<EntityComponent*> Entity::findComponentsByType(std::string type)
{
	std::vector<EntityComponent*> array;
	for (auto& component : components) {
		if (component->getType() == type) {
			array.push_back(component);
		}
	}
	return array;
}

void Entity::addComponent(EntityComponent* component)
{
	this->components.push_back(component);
}
