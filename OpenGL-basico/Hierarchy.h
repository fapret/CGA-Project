#pragma once
#include "Entity.h"
#include <glad/glad.h>
#include "btBulletDynamicsCommon.h"
#include <iostream>

class Hierarchy {
private:
	std::vector<Entity*> entities;
	Hierarchy() {
		this->collisionConfiguration = new btDefaultCollisionConfiguration();
		this->dispatcher = new btCollisionDispatcher(this->collisionConfiguration);
		this->overlappingPairCache = new btDbvtBroadphase();
		this->solver = new btSequentialImpulseConstraintSolver();

		// Create the dynamics world
		this->dynamicsWorld = new btDiscreteDynamicsWorld(this->dispatcher, this->overlappingPairCache, this->solver, this->collisionConfiguration);
		//this->dynamicsWorld->setGravity(btVector3(0, -9.8f, 0));
	};
	Entity* activeCamera;
	std::vector<GLuint> shaders;
	int spotlightsAmount;
	btDiscreteDynamicsWorld* dynamicsWorld;
	btDefaultCollisionConfiguration* collisionConfiguration;
	btCollisionDispatcher* dispatcher;
	btBroadphaseInterface* overlappingPairCache;
	btSequentialImpulseConstraintSolver* solver;
	~Hierarchy() {
		delete this->dynamicsWorld;
		delete this->solver;
		delete this->overlappingPairCache;
		delete this->dispatcher;
		delete this->collisionConfiguration;
	}
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
	void setGravity(float gravity = 9.8f);
	btDiscreteDynamicsWorld* getDynamicsWorld();
};