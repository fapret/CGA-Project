#pragma once
#include <string>
#include <vector>
#include "EntityComponent.h"

#ifdef USE_IMGUI
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"
#endif

class Entity {
private:
	std::string name;
	std::string id;
	std::vector<EntityComponent*> components;
public:
	std::string getName();
	void setName(std::string name);
	std::string getId();
	Entity();
	Entity(std::string name);
	Entity(std::string name, std::string id);
	~Entity();
	EntityComponent* findComponentByID(std::string id);
	std::vector<EntityComponent*> findComponentsByType(std::string type);
	void addComponent(EntityComponent* component);
#ifdef USE_IMGUI
	void drawProperties();
#endif
};