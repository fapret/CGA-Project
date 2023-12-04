#pragma once
#include "Entity.h"
#include <glad/glad.h>


class Hierarchy {
private:
	std::vector<Entity*> entities;
	Hierarchy() {}
	Entity* activeCamera;
	std::vector<GLuint> shaders;
	int spotlightsAmount;
public:
	static Hierarchy& getInstance();
	Hierarchy(const Hierarchy&) = delete;
	Hierarchy& operator=(const Hierarchy&) = delete;

	void addEntity(Entity* entity);
	void removeEntityById(std::string id);
	Entity* findEntityById(std::string id);
	Entity* findEntityByName(std::string name);
	void setActiveCamera(Entity* cam);
	Entity* getActiveCamera();
	std::vector<Entity*> getAllEntities();
	std::vector<GLuint> getShaders();
	void addShader(GLuint shaderId);
	int getAmountSpotlights();
	void incAmountSpotlights();
};