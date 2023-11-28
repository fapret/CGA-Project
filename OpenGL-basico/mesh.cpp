#include "mesh.h"


MeshData LoadMeshData(const std::string& pFile)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(pFile,
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_SortByPType);

	MeshData meshData;

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		std::cerr << "Assimp error: " << importer.GetErrorString() << std::endl;
		return meshData;
	}

	for (unsigned int m = 0; m < scene->mNumMeshes; ++m) {
		const aiMesh* mesh = scene->mMeshes[m];
		for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
			meshData.vertices.push_back(glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z));
			meshData.normals.push_back(glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z));

			if (mesh->HasTextureCoords(0)) {
				meshData.texCoords.push_back(glm::vec3(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y, 0.0f));
			}
		}
	}

	return meshData;
}

GLuint CreateMeshVAO(const MeshData& meshData, int mode)
{
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint vbo[3];
	glGenBuffers(3, vbo);

	GLuint drawMode;

	switch (mode)
	{
	case 1:
		drawMode = GL_STATIC_DRAW;
		break;
	case 2:
		drawMode = GL_STREAM_DRAW;
		break;
	case 3:
		drawMode = GL_DYNAMIC_DRAW;
		break;
	default:
		drawMode = GL_STATIC_DRAW;
	}

	// Vertex positions
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * meshData.vertices.size(), meshData.vertices.data(), drawMode);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	// Normals
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * meshData.normals.size(), meshData.normals.data(), drawMode);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	// Texture coordinates
	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * meshData.texCoords.size(), meshData.texCoords.data(), drawMode);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	glBindVertexArray(0);

	return vao;
}

void RenderMeshVAO(GLuint vao, int faceAmount) {
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, faceAmount);
	glBindVertexArray(0);
}