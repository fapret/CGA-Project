#include "BoundingBox.h"


void BoundingBox::update(const std::vector<glm::vec3>& vertices){
    minPoint = maxPoint = vertices[0];

    for (const auto& vertex : vertices) {
        minPoint = glm::min(minPoint, vertex);
        maxPoint = glm::max(maxPoint, vertex);
    }
}