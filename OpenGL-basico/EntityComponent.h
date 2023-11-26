#pragma once
#include <string>

class EntityComponent {
private:
	std::string type;
	std::string id;
public:
	std::string getType();
	std::string getId();
	EntityComponent();
	EntityComponent(std::string type);
#ifdef USE_IMGUI
	virtual void EditorPropertyDraw();
#endif
};