#pragma once
#include <string>
#ifdef USE_IMGUI
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"
#endif

class EntityComponent {
private:
	std::string type;
	std::string id;
public:
	std::string getType();
	std::string getId();
	EntityComponent();
	EntityComponent(std::string type);
	virtual void draw();
#ifdef USE_IMGUI
	virtual void EditorPropertyDraw();
#endif
};