#pragma once
#include "EntityComponent.h"
#include <btBulletDynamicsCommon.h>
#include "TransformComponent.h"

class ColliderComponent : public EntityComponent {
private:
	btRigidBody* rigidBody;
	TransformComponent* transform;

public:
	ColliderComponent();
	void draw(float deltaTime = 0.0f) override;
	void setUpCollission(int type, btScalar mass = 1.0, btScalar scale = 1.0, bool gravity = true, glm::vec3 offset = glm::vec3(0,0,0));
	btRigidBody* getRigidBody();
	void setFatherEntity(Entity* father) override;
	TransformComponent* getTransform();
#ifdef USE_IMGUI
	void EditorPropertyDraw() override;
#endif
};

