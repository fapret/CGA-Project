#include "mundo.h"


Mundo::Mundo(float alt, float anch, float prof) {
	altCol = alt;
	anchCol = anch;
	profCol = prof;
	pos = new Vector3(5, 0, 5);
	vel = new Vector3(0, 0, 0);
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

Vector3* Mundo::getVel() {
	return vel;
}

void Mundo::setVel(Vector3* vect) {
	vel = vect;
}

Vector3* Mundo::getPos() {
	return pos;
}

void Mundo::setPos(Vector3* vect) {
	pos = vect;
}

void Mundo::setPos(float x, float y, float z) {
	pos->setX(x);
	pos->setY(y);
	pos->setZ(z);
}

void Mundo::draw(Vector3** modelo, int caras) {
#pragma warning(disable : 4996)
	if (disList == -1) disList = drawFaces(modelo, caras);
	if (disList != -1) glCallList(disList);
#pragma warning(default : 4996)
}

void Mundo::draw() {
	if (vao != 0) {
		RenderMeshVAO(vao, meshData.vertices.size() / 3);
	}
}

void Mundo::loadMesh(const std::string& filename) {
	meshData = LoadMeshData(filename);
	vao = CreateMeshVAO(meshData);
}

