#pragma once
#include <glad/glad.h>
#include "SDL.h"
#include "SDL_opengl.h"
#include "FreeImage.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags
#include "Vector3.h"
#include <vector>
#include <iostream>

struct MeshData {
    std::vector<Vector3> vertices;
    std::vector<Vector3> normals;
    std::vector<Vector3> texCoords;
};

MeshData LoadMeshData(const std::string& pFile);

GLuint CreateMeshVAO(const MeshData& meshData, int mode = 1);

void RenderMeshVAO(GLuint vao, int faceAmount);

[[deprecated]]
Vector3** DoTheImportThing(const std::string& pFile, int& faceAmount);
[[deprecated]]
int drawFaces(Vector3** model, int faceAmount);