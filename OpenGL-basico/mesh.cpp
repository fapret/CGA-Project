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

	const aiMesh* mesh = scene->mMeshes[0];

	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
		meshData.vertices.push_back(Vector3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z));
		meshData.normals.push_back(Vector3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z));

		if (mesh->HasTextureCoords(0)) {
			meshData.texCoords.push_back(Vector3(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y, 0.0f));
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
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vector3) * meshData.vertices.size(), meshData.vertices.data(), drawMode);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Normals
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vector3) * meshData.normals.size(), meshData.normals.data(), drawMode);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Texture coordinates
	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vector3) * meshData.texCoords.size(), meshData.texCoords.data(), drawMode);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0);

	return vao;
}

void RenderMeshVAO(GLuint vao, int faceAmount) {
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, faceAmount * 3);
	glBindVertexArray(0);
}

Vector3** DoTheImportThing(const std::string& pFile, int& faceAmount) {
	// Create an instance of the Importer class
	Assimp::Importer importer;

	// And have it read the given file with some example postprocessing
	// Usually - if speed is not the most important aspect for you - you'll
	// probably to request more postprocessing than we do in this example.
	const aiScene* scene = importer.ReadFile(pFile,
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_SortByPType);
	// If the import failed, report it

	// Now we can access the file's contents.

	// We're done. Everything will be cleaned up by the importer destructor

	faceAmount = scene->mMeshes[0]->mNumFaces;
	Vector3** model = new Vector3 * [3];
	model[0] = new Vector3[faceAmount * 3];
	model[1] = new Vector3[faceAmount * 3];
	model[2] = new Vector3[faceAmount * 3];
	for (int i = 0; i < faceAmount; i++) {
		//VERTICES
		model[0][i].setX(scene->mMeshes[0]->mVertices[scene->mMeshes[0]->mFaces[i].mIndices[0]].x);
		model[0][i].setY(scene->mMeshes[0]->mVertices[scene->mMeshes[0]->mFaces[i].mIndices[0]].y);
		model[0][i].setZ(scene->mMeshes[0]->mVertices[scene->mMeshes[0]->mFaces[i].mIndices[0]].z);
		model[0][faceAmount + i].setX(scene->mMeshes[0]->mVertices[scene->mMeshes[0]->mFaces[i].mIndices[1]].x);
		model[0][faceAmount + i].setY(scene->mMeshes[0]->mVertices[scene->mMeshes[0]->mFaces[i].mIndices[1]].y);
		model[0][faceAmount + i].setZ(scene->mMeshes[0]->mVertices[scene->mMeshes[0]->mFaces[i].mIndices[1]].z);
		model[0][faceAmount * 2 + i].setX(scene->mMeshes[0]->mVertices[scene->mMeshes[0]->mFaces[i].mIndices[2]].x);
		model[0][faceAmount * 2 + i].setY(scene->mMeshes[0]->mVertices[scene->mMeshes[0]->mFaces[i].mIndices[2]].y);
		model[0][faceAmount * 2 + i].setZ(scene->mMeshes[0]->mVertices[scene->mMeshes[0]->mFaces[i].mIndices[2]].z);
		//NORMALES
		model[1][i].setX(scene->mMeshes[0]->mNormals[scene->mMeshes[0]->mFaces[i].mIndices[0]].x);
		model[1][i].setY(scene->mMeshes[0]->mNormals[scene->mMeshes[0]->mFaces[i].mIndices[0]].y);
		model[1][i].setZ(scene->mMeshes[0]->mNormals[scene->mMeshes[0]->mFaces[i].mIndices[0]].z);
		model[1][faceAmount + i].setX(scene->mMeshes[0]->mNormals[scene->mMeshes[0]->mFaces[i].mIndices[1]].x);
		model[1][faceAmount + i].setY(scene->mMeshes[0]->mNormals[scene->mMeshes[0]->mFaces[i].mIndices[1]].y);
		model[1][faceAmount + i].setZ(scene->mMeshes[0]->mNormals[scene->mMeshes[0]->mFaces[i].mIndices[1]].z);
		model[1][faceAmount * 2 + i].setX(scene->mMeshes[0]->mNormals[scene->mMeshes[0]->mFaces[i].mIndices[2]].x);
		model[1][faceAmount * 2 + i].setY(scene->mMeshes[0]->mNormals[scene->mMeshes[0]->mFaces[i].mIndices[2]].y);
		model[1][faceAmount * 2 + i].setZ(scene->mMeshes[0]->mNormals[scene->mMeshes[0]->mFaces[i].mIndices[2]].z);
		//UVs
		model[2][i].setX(scene->mMeshes[0]->mTextureCoords[0][scene->mMeshes[0]->mFaces[i].mIndices[0]].x);
		model[2][i].setY(scene->mMeshes[0]->mTextureCoords[0][scene->mMeshes[0]->mFaces[i].mIndices[0]].y);
		model[2][i].setZ(scene->mMeshes[0]->mTextureCoords[0][scene->mMeshes[0]->mFaces[i].mIndices[0]].z);
		model[2][faceAmount + i].setX(scene->mMeshes[0]->mTextureCoords[0][scene->mMeshes[0]->mFaces[i].mIndices[1]].x);
		model[2][faceAmount + i].setY(scene->mMeshes[0]->mTextureCoords[0][scene->mMeshes[0]->mFaces[i].mIndices[1]].y);
		model[2][faceAmount + i].setZ(scene->mMeshes[0]->mTextureCoords[0][scene->mMeshes[0]->mFaces[i].mIndices[1]].z);
		model[2][faceAmount * 2 + i].setX(scene->mMeshes[0]->mTextureCoords[0][scene->mMeshes[0]->mFaces[i].mIndices[2]].x);
		model[2][faceAmount * 2 + i].setY(scene->mMeshes[0]->mTextureCoords[0][scene->mMeshes[0]->mFaces[i].mIndices[2]].y);
		model[2][faceAmount * 2 + i].setZ(scene->mMeshes[0]->mTextureCoords[0][scene->mMeshes[0]->mFaces[i].mIndices[2]].z);

	}
	return model;
};

int drawFaces(Vector3** model, int faceAmount) {
	int displayList = glGenLists(1);
	glNewList(displayList, GL_COMPILE);
	for (int i = 0; i < faceAmount; i++) {
		glBegin(GL_TRIANGLES);
		glTexCoord3f(model[2][i].getX(), model[2][i].getY(), model[2][i].getZ());
		glNormal3f(model[1][i].getX(), model[1][i].getY(), model[1][i].getZ());
		glVertex3f(model[0][i].getX(), model[0][i].getY(), model[0][i].getZ());
		glTexCoord3f(model[2][faceAmount + i].getX(), model[2][faceAmount + i].getY(), model[2][faceAmount + i].getZ());
		glNormal3f(model[1][faceAmount + i].getX(), model[1][faceAmount + i].getY(), model[1][faceAmount + i].getZ());
		glVertex3f(model[0][faceAmount + i].getX(), model[0][faceAmount + i].getY(), model[0][faceAmount + i].getZ());
		glTexCoord3f(model[2][faceAmount * 2 + i].getX(), model[2][faceAmount * 2 + i].getY(), model[2][faceAmount * 2 + i].getZ());
		glNormal3f(model[1][faceAmount * 2 + i].getX(), model[1][faceAmount * 2 + i].getY(), model[1][faceAmount * 2 + i].getZ());
		glVertex3f(model[0][faceAmount * 2 + i].getX(), model[0][faceAmount * 2 + i].getY(), model[0][faceAmount * 2 + i].getZ());
		glEnd();
	}
	glEndList();
	return displayList;
}