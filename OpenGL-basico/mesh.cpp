#include "mesh.h"





/*
void MeshData::LoadMeshData(const std::string & pFile, int drawMode) {

	GLuint mode;
	switch (drawMode)
	{
	case 1:
		mode = GL_STATIC_DRAW;
		break;
	case 2:
		mode = GL_STREAM_DRAW;
		break;
	case 3:
		mode = GL_DYNAMIC_DRAW;
		break;
	default:
		mode = GL_STATIC_DRAW;
	}

	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(pFile,
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_SortByPType);


	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		std::cerr << "Assimp error: " << importer.GetErrorString() << std::endl;
		return;
	}

	for (unsigned int m = 0; m < scene->mNumMeshes; m++) {
		// crear un VAO, VBO y texture id


		// texutra
		GLuint texId;
		glGenTextures(1, &texId);
		glBindTexture(GL_TEXTURE_2D, texId);
		this->textureIds.push_back(texId);

		if (scene->mMeshes[m]->mMaterialIndex > 0) {
			// check si el material tiene textura, si no usar un default
			aiMaterial* material = scene->mMaterials[scene->mMeshes[m]->mMaterialIndex];

			if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
				aiString texturePath;
				if (material->GetTexture(aiTextureType_DIFFUSE, 0, &texturePath) == AI_SUCCESS) {
					// el material tiene una textura
					FREE_IMAGE_FORMAT fif = FreeImage_GetFIFFromFilename(texturePath.C_Str());
					FIBITMAP* bitmap = FreeImage_Load(fif, texturePath.C_Str());

					bitmap = FreeImage_ConvertTo24Bits(bitmap);
					int width = FreeImage_GetWidth(bitmap);
					int height = FreeImage_GetHeight(bitmap);
					void* image = FreeImage_GetBits(bitmap);

					glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
					FreeImage_Unload(bitmap);
				}
			}
		}

		// VAO
		GLuint vaoId;
		glGenVertexArrays(1, &vaoId);
		this->VAO.push_back(vaoId);
		glBindVertexArray(vaoId);

		// VBO
		GLuint vboId;
		glGenBuffers(1, &vboId);
		this->VBO.push_back(vboId);
		glBindBuffer(GL_ARRAY_BUFFER, vboId);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * scene->mMeshes[m]->mNumVertices * 3, scene->mMeshes[m]->mVertices, mode);


		// Attribute Pointer
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		// EBO
		GLuint eboId;
		glGenBuffers(1, &eboId);
		this->EBO.push_back(eboId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboId);
		this->eboSize.push_back(scene->mMeshes[m]->mFaces[0].mNumIndices);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * scene->mMeshes[m]->mNumFaces * 3, scene->mMeshes[m]->mFaces[0].mIndices, mode);

		// Unbind VBO and VAO (optional but recommended)

	}
}

void MeshData::RenderMesh()
{
	GLuint shaderProgram = Hierarchy::getInstance().getShaders().at(0);
	glUseProgram(shaderProgram);

	Entity* activeCamera = Hierarchy::getInstance().getActiveCamera();
	CameraComponent* cam = (CameraComponent*)activeCamera->findComponentsByType("CameraComponent").at(0);

	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(cam->getView()));
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(cam->getProjection()));

	for (int i = 0; i < VAO.size(); i++) {
		glUniform1i(glGetUniformLocation(shaderProgram, "textureBuff"), 0);

		glBindVertexArray(VAO.at(i));
		glDrawElements(GL_TRIANGLES, eboSize.at(i), GL_UNSIGNED_INT, 0);
	}
}
*/


/*
std::vector<MeshData> LoadMeshData(const std::string& pFile)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(pFile,
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_SortByPType);

	std::vector<MeshData> meshDataArray;

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		std::cerr << "Assimp error: " << importer.GetErrorString() << std::endl;
		return meshDataArray;
	}

	for (unsigned int m = 0; m < scene->mNumMeshes; ++m) {
		MeshData meshData;

		const aiMesh* mesh = scene->mMeshes[m];
		for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {
			const aiFace& face = mesh->mFaces[i];
			for (unsigned int j = 0; j < face.mNumIndices; ++j) {
				meshData.indices.push_back(face.mIndices[j]);
			}
		}

		for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
			meshData.vertices.push_back(glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z));
			meshData.normals.push_back(glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z));

			if (mesh->HasTextureCoords(0)) {
				meshData.texCoords.push_back(glm::vec3(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y, 0.0f));
			}
		}

		if (mesh->mMaterialIndex > 0) {
			aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];



			aiColor3D diffuseColor(0.f, 0.f, 0.f);
			if (material->Get(AI_MATKEY_COLOR_DIFFUSE, diffuseColor) == AI_SUCCESS) {
				std::cout << "Diffuse Color: " << diffuseColor.r << ", " << diffuseColor.g << ", " << diffuseColor.b << std::endl;
			}

			// Process other material properties...

			// Check if the material has a texture
			if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
				aiString texturePath;
				if (material->GetTexture(aiTextureType_DIFFUSE, 0, &texturePath) == AI_SUCCESS) {
					GLuint textureID;
					glActiveTexture(GL_TEXTURE0);
					glGenTextures(1, &textureID);
					glBindTexture(GL_TEXTURE_2D, textureID);

					FREE_IMAGE_FORMAT fif = FreeImage_GetFIFFromFilename(texturePath.C_Str());
					FIBITMAP* bitmap = FreeImage_Load(fif, texturePath.C_Str());
					bitmap = FreeImage_ConvertTo24Bits(bitmap);
					int width = FreeImage_GetWidth(bitmap);
					int height = FreeImage_GetHeight(bitmap);
					void* image = FreeImage_GetBits(bitmap);

					glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
					glBindTexture(GL_TEXTURE_2D, 0);
					meshData.textureId = textureID;
				}
			}
		}

		meshDataArray.push_back(meshData);
	}


	return meshDataArray;
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), nullptr);

	// Normals
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * meshData.normals.size(), meshData.normals.data(), drawMode);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), nullptr);

	// Texture coordinates
	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * meshData.texCoords.size(), meshData.texCoords.data(), drawMode);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), nullptr);

	// Indices
	GLuint ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * meshData.indices.size(), meshData.indices.data(), GL_STATIC_DRAW);

	glBindVertexArray(0);

	return vao;
}


std::vector<GLuint> CreateMultipleMeshVAO(const std::vector<MeshData>& meshData, int mode) {
	std::vector<GLuint> vaos;

	for (const auto& data : meshData) {
		GLuint vao = CreateMeshVAO(data, mode);
		vaos.push_back(vao);
	}

	return vaos;
}

void RenderMeshVAO(GLuint vao, int faceAmount, GLuint textureId) {
	glBindVertexArray(vao);

	if (textureId > -1) {
		glBindTexture(GL_TEXTURE_2D, textureId);
		Hierarchy& hierarchy = Hierarchy::getInstance();
		GLuint textureLocation = glGetUniformLocation(hierarchy.getShaders()[0], "textureSampler");
		glUniform1i(textureLocation, 0);
	}
	glDrawElements(GL_TRIANGLES, 3 * faceAmount, GL_UNSIGNED_INT, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void RenderMultipleMeshVAO(std::vector<GLuint> vaos, std::vector<int> faceAmounts, std::vector<GLuint> textureIds)
{
	for (size_t i = 0; i < vaos.size(); ++i) {
		if(i < textureIds.size())
			RenderMeshVAO(vaos.at(i), faceAmounts.at(i), textureIds.at(i));
		else
			RenderMeshVAO(vaos.at(i), faceAmounts.at(i), -1);
	}
}
*/