#pragma once
#include "mesh.h"
#include <SDL_opengl.h>


class Mundo {
private:
	float altCol;
	float anchCol;
	float profCol;
	glm::vec3* pos;
	glm::vec3* vel;
	int disList;
	GLuint vao;
	MeshData meshData;

public:
	Mundo(float, float, float);
	~Mundo();
	float getAltCol();
	float getAnchCol();
	float getProfCol();
	glm::vec3* getPos();
	void setPos(float, float, float);
	void setPos(glm::vec3*);
	glm::vec3* getVel();
	void setVel(glm::vec3*);
	[[deprecated]]
	void draw(glm::vec3**, int);
	void draw();
	void loadMesh(const std::string& filename);
};