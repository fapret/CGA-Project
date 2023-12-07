#include "MeshComponent.h"

float MeshComponent::calculateDistance(const glm::vec3& point1, const glm::vec3& point2)
{
	float distance = glm::sqrt(glm::pow(point2.x - point1.x, 2) +
		glm::pow(point2.y - point1.y, 2) +
		glm::pow(point2.z - point1.z, 2));
	return distance;
}

MeshComponent::MeshComponent() : EntityComponent("MeshComponent")
{
	this->maxViewDistance = 10000.0f;
	this->transform = new TransformComponent();
	this->animator = NULL;
}

MeshComponent::MeshComponent(float maxDistance) : EntityComponent("MeshComponent")
{
	this->maxViewDistance = maxDistance;
	this->transform = new TransformComponent();
	this->animator = NULL;
}

void MeshComponent::draw(float deltaTime)
{
	Hierarchy& hierarchy = Hierarchy::getInstance();
	Entity* camEntity = hierarchy.getActiveCamera();
	if (camEntity != nullptr) {
		std::vector<EntityComponent*> camTransformList = camEntity->findComponentsByType("TransformComponent");
		if (camTransformList.empty()) {
			return;
		}
		TransformComponent* camTransform = (TransformComponent*)camTransformList.at(0);
		float distance = calculateDistance(camTransform->getPosition(), transform->getPosition());

		// Find the appropriate LOD level based on distance
		LOD* selectedLOD = nullptr;
		float minDistanceDifference = std::numeric_limits<float>::max();

		for (auto& lod : LodLevels) {
			float distanceDifference = std::abs(distance - lod.viewDistance);
			if (distanceDifference < minDistanceDifference) {
				minDistanceDifference = distanceDifference;
				selectedLOD = &lod;
			}
		}

		if (selectedLOD) {
			glm::mat4 model = glm::mat4(1.0f);
			GLuint shaderProgram = hierarchy.getShaders().at(0);
			if (animator != NULL) {
				animator->UpdateAnimation(deltaTime);
				auto transforms = animator->GetFinalBoneMatrices();
				for (int i = 0; i < transforms.size(); ++i) {
					std::string uniformName = "finalBonesMatrices[" + std::to_string(i) + "]";
					GLint uniformLocation = glGetUniformLocation(shaderProgram, uniformName.c_str());
					if (uniformLocation != -1) {
						glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(transforms[i]));
					}
				}
			}
			model = glm::translate(model, glm::vec3(-transform->getPosition().x, -transform->getPosition().y, -transform->getPosition().z));
			model = glm::rotate(model, glm::radians(transform->getRotation().x), glm::vec3(1.0f, 0.0f, 0.0f)); // Rotate around X axis
			model = glm::rotate(model, glm::radians(transform->getRotation().y), glm::vec3(0.0f, 1.0f, 0.0f)); // Rotate around Y axis
			model = glm::rotate(model, glm::radians(transform->getRotation().z), glm::vec3(0.0f, 0.0f, 1.0f)); // Rotate around Z axis
			model = glm::scale(model, glm::vec3(transform->getScale().x, transform->getScale().y, transform->getScale().z));

		
			int modelIndex = glGetUniformLocation(hierarchy.getShaders()[0], "model");
			glUniformMatrix4fv(modelIndex, 1, GL_FALSE, glm::value_ptr(model));

			GLint ambientColorLoc = glGetUniformLocation(shaderProgram, "ambientColor");
			CameraComponent* camComp = (CameraComponent*) hierarchy.getActiveCamera()->findComponentsByType("CameraComponent").at(0);
			glUniform3f(ambientColorLoc, camComp->getAmbientLight().x, camComp->getAmbientLight().y, camComp->getAmbientLight().z); // Set ambient light color to (0.2, 0.2, 0.2)

			SkyboxComponent* camSky = (SkyboxComponent*)hierarchy.getActiveCamera()->findComponentsByType("SkyboxComponent").at(0);
			if (camSky) {
				GLint lightDirectionLoc = glGetUniformLocation(shaderProgram, "lightDirection");
				glUniform3f(lightDirectionLoc, camSky->getSunDirection().x, camSky->getSunDirection().y, camSky->getSunDirection().z);
				GLint lightColorLoc = glGetUniformLocation(shaderProgram, "lightColor");
				glUniform3f(lightColorLoc, camSky->getSunColor().x, camSky->getSunColor().y, camSky->getSunColor().z);
			}

			for (int i = 0; i < selectedLOD->numOfMeshes; i++) {
				selectedLOD->meshData.at(i)->Draw(shaderProgram);
			}
		}
		glm::mat4 model = glm::mat4(1.0f);
		int modelIndex = glGetUniformLocation(hierarchy.getShaders()[0], "model");
	}
}

void MeshComponent::setMaxViewDistance(float maxView)
{
	this->maxViewDistance = maxView;
}

void MeshComponent::addLOD(LOD lod)
{
	this->LodLevels.push_back(lod);
}

int MeshComponent::getMaxViewDistance()
{
	return maxViewDistance;
}

void MeshComponent::setFatherEntity(Entity* father)
{
	EntityComponent::setFatherEntity(father);
	std::vector<EntityComponent*> transformList = father->findComponentsByType("TransformComponent");
	if (transformList.size() == 0) {
		father->addComponent(transform);
	}
}

void MeshComponent::addAnimation(const std::string& pFile)
{
	Animation* danceAnimation = new Animation(pFile, this->LodLevels.at(0).meshData.at(0));
	this->animator = new Animator(danceAnimation);
}

Animator* MeshComponent::getAnimator()
{
	return animator;
}

#ifdef USE_IMGUI
void MeshComponent::EditorPropertyDraw()
{
	EntityComponent::EditorPropertyDraw();
}
#endif

unsigned int TextureFromFile(const char* path)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	FREE_IMAGE_FORMAT imageFormat = FreeImage_GetFIFFromFilename(path);

	if (imageFormat == FIF_UNKNOWN) {
		// Handle unknown file format
		return -1;
	}

	FIBITMAP* image = FreeImage_Load(imageFormat, path, 0);

	if (image)
	{
		FIBITMAP* image32 = FreeImage_ConvertTo32Bits(image);
		FreeImage_Unload(image);

		int width = FreeImage_GetWidth(image32);
		int height = FreeImage_GetHeight(image32);

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, FreeImage_GetBits(image32));
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		FreeImage_Unload(image32);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
	}

	return textureID;
}

std::vector<Texture> loadMaterialTextures(LOD lod, aiMaterial* mat, aiTextureType type, std::string typeName)
{
	std::vector<Texture> textures;
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		// check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
		bool skip = false;
		for (unsigned int j = 0; j < lod.textures_loaded.size(); j++)
		{
			if (std::strcmp(lod.textures_loaded[j].path.data(), str.C_Str()) == 0)
			{
				textures.push_back(lod.textures_loaded[j]);
				skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
				break;
			}
		}
		if (!skip)
		{   // if texture hasn't been loaded already, load it
			Texture texture;
			texture.id = TextureFromFile(str.C_Str());
			texture.type = typeName;
			texture.path = str.C_Str();
			textures.push_back(texture);
			lod.textures_loaded.push_back(texture);  // store it as texture loaded for entire model, to ensure we won't unnecessary load duplicate textures.
		}
	}
	return textures;
}

void SetVertexBoneDataToDefault(Vertex& vertex)
{
	for (int i = 0; i < MAX_BONE_INFLUENCE; i++)
	{
		vertex.m_BoneIDs[i] = -1;
		vertex.m_Weights[i] = 0.0f;
	}
}

LOD createLOD(const std::string& pFile, float viewDistance)
{
	LOD lod;
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(pFile,
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_SortByPType);


	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		std::cerr << "Assimp error: " << importer.GetErrorString() << std::endl;
		return lod;
	}

	for (unsigned int m = 0; m < scene->mNumMeshes; m++) {
		aiMesh* mesh = scene->mMeshes[m];
		std::vector<unsigned int> indices;
		for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {
			const aiFace& face = mesh->mFaces[i];
			for (unsigned int j = 0; j < face.mNumIndices; ++j) {
				indices.push_back(face.mIndices[j]);
			}
		}

		std::vector<Vertex> vertices;
		for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
			Vertex topush = Vertex(
				glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z),
				glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z),
				glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y),
				glm::vec3(mesh->mTangents[i].x, mesh->mTangents[i].y, mesh->mTangents[i].z),
				glm::vec3(mesh->mBitangents[i].x, mesh->mBitangents[i].y, mesh->mBitangents[i].z)
			);
			SetVertexBoneDataToDefault(topush);
			vertices.push_back(topush);
		}

		std::vector<Texture> textures;
		if (mesh->mMaterialIndex > 0) {
			// check si el material tiene textura, si no usar un default
			aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

			// 1. diffuse maps
			std::vector<Texture> diffuseMaps = loadMaterialTextures(lod, material, aiTextureType_DIFFUSE, "texture_diffuse");
			textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
			// 2. specular maps
			std::vector<Texture> specularMaps = loadMaterialTextures(lod, material, aiTextureType_SPECULAR, "texture_specular");
			textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
			// 3. normal maps
			std::vector<Texture> normalMaps = loadMaterialTextures(lod, material, aiTextureType_HEIGHT, "texture_normal");
			textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
			// 4. height maps
			std::vector<Texture> heightMaps = loadMaterialTextures(lod, material, aiTextureType_AMBIENT, "texture_height");
			textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

			if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
				aiString texturePath;
				if (material->GetTexture(aiTextureType_DIFFUSE, 0, &texturePath) == AI_SUCCESS) {
					// el material tiene una textura difusa
				}
			}
		}

		Mesh* newMesh = new Mesh(vertices, indices, textures, mesh, scene);
		lod.meshData.push_back(newMesh);
	}

	lod.viewDistance = viewDistance;
	lod.numOfMeshes = scene->mNumMeshes;
	return lod;
}