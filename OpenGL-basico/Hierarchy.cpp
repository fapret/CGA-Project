#include "Hierarchy.h"

Hierarchy& Hierarchy::getInstance()
{
    static Hierarchy instance;  // This line ensures that the instance is created once
    return instance;
}

void Hierarchy::addEntity(Entity* entity, bool start)
{
    if (start)
        this->entities.insert(this->entities.begin(), entity);
    else
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

std::vector<GLuint> Hierarchy::getShaders()
{
    return shaders;
}

void Hierarchy::addShader(GLuint shaderId)
{
    shaders.push_back(shaderId);
}

int Hierarchy::getAmountSpotlights()
{
    return spotlightsAmount;
}

void Hierarchy::incAmountSpotlights()
{
    this->spotlightsAmount++;
}

void Hierarchy::setGravity(float gravity)
{
    this->dynamicsWorld->setGravity(btVector3(0, gravity, 0));
}

void Hierarchy::addDynamicObject(EntityComponent* object)
{
    dynamicObjects.push_back(object);
}

std::vector<EntityComponent*> Hierarchy::getDynamicObjects()
{
    return dynamicObjects;
}



btDiscreteDynamicsWorld* Hierarchy::getDynamicsWorld()
{
    return dynamicsWorld;
}

