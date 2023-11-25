#pragma once
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags
#include "Vector3.h"
#include <SDL.h>
#include <SDL_opengl.h>

Vector3** DoTheImportThing(const std::string& pFile, int& faceAmount);

int drawFaces(Vector3** model, int faceAmount);