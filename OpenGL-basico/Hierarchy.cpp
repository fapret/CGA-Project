#include "Hierarchy.h"

Hierarchy& Hierarchy::getInstance()
{
    static Hierarchy instance;  // This line ensures that the instance is created once
    return instance;
}

void Hierarchy::addEntity(Entity* entity)
{
	this->entities.push_back(entity);
}

void Hierarchy::removeEntityById(std::string id)
{
    auto it = std::find_if(entities.begin(), entities.end(),
        [&id](Entity* entity) { return entity->getId() == id; });

    if (it != entities.end()) {
        // Erase the entity from the vector
        entities.erase(it);
    }
}

Entity* Hierarchy::findEntityById(std::string id)
{
    for (auto& entity : entities) {
        if (entity->getId() == id) {
            return entity;
        }
    }
    return nullptr;
}

Entity* Hierarchy::findEntityByName(std::string name)
{
    for (auto& entity : entities) {
        if (entity->getName() == name) {
            return entity;
        }
    }
    return nullptr;
}

void Hierarchy::setActiveCamera(Entity* cam)
{
    this->activeCamera = cam;
}

Entity* Hierarchy::getActiveCamera()
{
    return activeCamera;
}

std::vector<Entity*> Hierarchy::getAllEntities()
{
    return entities;
}
