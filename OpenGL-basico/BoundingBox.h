#pragma once
#include <glm/glm.hpp> 
#include <vector>


class BoundingBox {
private:
	glm::vec3 minPoint;
	glm::vec3 maxPoint;
public:
	void update(const std::vector<glm::vec3>& vertices);
};

