#pragma once
#include "EntityComponent.h"
#include "Hierarchy.h"
#include <SDL_stdinc.h>
#include "btBulletDynamicsCommon.h"

class CollisionComponent : public EntityComponent {
private:
	btDiscreteDynamicsWorld* dynamicsWorld;
public:
	void setDynamicsWorld(btDiscreteDynamicsWorld* dynamicsWorld);
	void setGravity();

#ifdef USE_IMGUI
	void EditorPropertyDraw() override;
#endif
}; 
