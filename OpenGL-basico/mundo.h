#pragma once
#include "mesh.h"
#include "Vector3.h"
#include <SDL_opengl.h>


class Mundo {
private:
	float altCol;
	float anchCol;
	float profCol;
	Vector3* pos;
	Vector3* vel;
	int disList;

public:
	Mundo(float, float, float);
	~Mundo();
	float getAltCol();
	float getAnchCol();
	float getProfCol();
	Vector3* getPos();
	void setPos(float, float, float);
	void setPos(Vector3*);
	Vector3* getVel();
	void setVel(Vector3*);
	void draw(Vector3**, int);
};