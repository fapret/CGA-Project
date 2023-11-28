#include "mundo.h"


Mundo::Mundo(float alt, float anch, float prof) {
	altCol = alt;
	anchCol = anch;
	profCol = prof;
	pos = new glm::vec3(5, 0, 5);
	vel = new glm::vec3(0, 0, 0);
	disList = -1;
	vao = 0;
}

Mundo::~Mundo() {
	delete pos;
	delete vel;

	if (vao != 0) {
		glDeleteVertexArrays(1, &vao);
	}
}

float Mundo::getAltCol() {
	return altCol;
}
float Mundo::getAnchCol() {
	return anchCol;
}
float Mundo::getProfCol() {
	return profCol;
}

glm::vec3* Mundo::getVel() {
	return vel;
}

void Mundo::setVel(glm::vec3* vect) {
	vel = vect;
}

glm::vec3* Mundo::getPos() {
	return pos;
}

void Mundo::setPos(glm::vec3* vect) {
	pos = vect;
}

void Mundo::setPos(float x, float y, float z) {
	pos->x = x;
	pos->y = y;
	pos->z = z;
}

void Mundo::draw() {
	if (vao != 0) {
		RenderMeshVAO(vao, meshData.vertices.size());
	}
}

void Mundo::loadMesh(const std::string& filename) {
	meshData = LoadMeshData(filename);
	vao = CreateMeshVAO(meshData);
}

