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
}

MeshComponent::MeshComponent(float maxDistance) : EntityComponent("MeshComponent")
{
	this->maxViewDistance = maxDistance;
	this->transform = new TransformComponent();
}

void MeshComponent::draw()
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
			model = glm::translate(model, glm::vec3(-transform->getPosition().x, -transform->getPosition().y, -transform->getPosition().z));
			model = glm::rotate(model, glm::radians(transform->getRotation().x), glm::vec3(1.0f, 0.0f, 0.0f)); // Rotate around X axis
			model = glm::rotate(model, glm::radians(transform->getRotation().y), glm::vec3(0.0f, 1.0f, 0.0f)); // Rotate around Y axis
			model = glm::rotate(model, glm::radians(transform->getRotation().z), glm::vec3(0.0f, 0.0f, 1.0f)); // Rotate around Z axis
			model = glm::scale(model, glm::vec3(transform->getScale().x, transform->getScale().y, transform->getScale().z));

		
			int modelIndex = glGetUniformLocation(hierarchy.getShaders()[0], "model");
			glUniformMatrix4fv(modelIndex, 1, GL_FALSE, glm::value_ptr(model));
			for (int i = 0; i < selectedLOD->numOfMeshes; i++) {
				selectedLOD->meshData[i]->Draw(shaderProgram);
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

#ifdef USE_IMGUI
void MeshComponent::EditorPropertyDraw()
{
	EntityComponent::EditorPropertyDraw();
}
#endif

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
		const aiMesh* mesh = scene->mMeshes[m];
		std::vector<unsigned int> indices;
		for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {
			const aiFace& face = mesh->mFaces[i];
			for (unsigned int j = 0; j < face.mNumIndices; ++j) {
				indices.push_back(face.mIndices[j]);
			}
		}

		std::vector<Vertex> vertices;
		for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
			vertices.push_back(Vertex(
				glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z),
				glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z),
				glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y),
				glm::vec3(mesh->mTangents[i].x, mesh->mTangents[i].y, mesh->mTangents[i].z),
				glm::vec3(mesh->mBitangents[i].x, mesh->mBitangents[i].y, mesh->mBitangents[i].z)
			));
		}

		std::vector<Texture> textures;
		if (mesh->mMaterialIndex > 0) {
			// check si el material tiene textura, si no usar un default
			aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

			if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
				aiString texturePath;
				if (material->GetTexture(aiTextureType_DIFFUSE, 0, &texturePath) == AI_SUCCESS) {
					// el material tiene una textura difusa
				}
			}
		}

		Mesh* newMesh = new Mesh(vertices, indices, textures);
		lod.meshData.push_back(newMesh);
	}

	lod.viewDistance = viewDistance;
	lod.numOfMeshes = scene->mNumMeshes;
	return lod;
}