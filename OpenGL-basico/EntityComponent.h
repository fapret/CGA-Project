#pragma once
#ifndef ENTITYCOMPONENT
#define ENTITYCOMPONENT
#include <string>
#ifdef USE_IMGUI
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"
#endif

class Entity;

class EntityComponent {
private:
	std::string type;
	std::string id;
	Entity* father;
public:
	std::string getType();
	std::string getId();
	EntityComponent();
	EntityComponent(std::string type);
	void setFatherEntity(Entity* father);
	Entity* getFatherEntity();
	virtual void draw();
#ifdef USE_IMGUI
	virtual void EditorPropertyDraw();
#endif
};
#endif