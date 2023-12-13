#include "TerrainComponent.h"
#include <iostream>

void TerrainComponent::calculateNormal(int x, int y) {
    glm::vec3 normal = glm::vec3(0.0f, 0.0f, 0.0f);

    if (x > 0 && y > 0 && x < width - 1 && y < height - 1) {
        // Get the vertices and their heights
        glm::vec3 v1 = glm::vec3(x * scale, vertices[(y - 1) * width * 3 + x * 3 + 1], (y - 1) * scale);
        glm::vec3 v2 = glm::vec3((x - 1) * scale, vertices[y * width * 3 + (x - 1) * 3 + 1], y * scale);
        glm::vec3 v3 = glm::vec3((x + 1) * scale, vertices[y * width * 3 + (x + 1) * 3 + 1], y * scale);
        glm::vec3 v4 = glm::vec3(x * scale, vertices[(y + 1) * width * 3 + x * 3 + 1], (y + 1) * scale);

        // Calculate the normal for the two triangles
        glm::vec3 e1 = v3 - v1;
        glm::vec3 e2 = v2 - v1;
        glm::vec3 normal1 = glm::cross(e1, e2);

        e1 = v4 - v2;
        e2 = v3 - v2;
        glm::vec3 normal2 = glm::cross(e1, e2);

        // Accumulate the normals
        normal += glm::normalize(normal1);
        normal += glm::normalize(normal2);

        // Average the normals
        normal /= 2.0f;

        // Set the normal for the vertex
        normals[(y * width + x) * 3] = normal.x;
        normals[(y * width + x) * 3 + 1] = normal.y;
        normals[(y * width + x) * 3 + 2] = normal.z;
    }
    // If it's a border vertex, set the normal to the up direction (flat terrain)
    else if (y == 0 || y == height - 1) {
        normals[(y * width + x) * 3] = 0.0f;
        normals[(y * width + x) * 3 + 1] = 1.0f;
        normals[(y * width + x) * 3 + 2] = 0.0f;
    }
    else if (x == 0 || x == width - 1) {
        normals[(y * width + x) * 3] = 0.0f;
        normals[(y * width + x) * 3 + 1] = 1.0f;
        normals[(y * width + x) * 3 + 2] = 0.0f;
    }
}



TerrainComponent::TerrainComponent() : EntityComponent("TerrainComponent")
{
}

TerrainComponent::~TerrainComponent()
{
    delete[] vertices;
    delete[] indices;
    delete[] textureCoords;
    delete[] normals;

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
}

void TerrainComponent::loadHeightmap(const char* filePath, float scale, float heightScale)
{
    this->scale = scale;
    this->heightScale = heightScale;
    // Load the image using FreeImage
    FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
    FIBITMAP* dib = nullptr;

    fif = FreeImage_GetFileType(filePath, 0);
    if (fif == FIF_UNKNOWN)
        fif = FreeImage_GetFIFFromFilename(filePath);

    if (fif == FIF_UNKNOWN)
        throw std::runtime_error("Unsupported image format");

    dib = FreeImage_Load(fif, filePath);

    if (!dib)
        throw std::runtime_error("Failed to load heightmap image");

    // Get image dimensions
    width = FreeImage_GetWidth(dib);
    height = FreeImage_GetHeight(dib);

    // Allocate memory for vertices
    vertices = new float[width * height * 3];
    indices = new unsigned int[(width - 1) * (height - 1) * 6];
    normals = new float[width * height * 3];
    textureCoords = new float[width * height * 2];

    



    // Generate texture coordinates
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            unsigned int index = (y * width + x) * 2;
            textureCoords[index] = static_cast<float>(x) / (width - 1) * 500.0f;
            textureCoords[index + 1] = static_cast<float>(y) / (height - 1) * 500.0f;
        }
    }

    // Calculate normals
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            unsigned int index = (y * width + x) * 3;
            calculateNormal(x, y);
        }
    }

    // Generate vertices and indices
    // Adjust scale if needed
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            unsigned int index = (y * width + x) * 3;
            RGBQUAD color;
            FreeImage_GetPixelColor(dib, x, y, &color);

            vertices[index] = x * scale;
            vertices[index + 1] = color.rgbRed * scale * heightScale;
            vertices[index + 2] = y * scale;
        }
    }

    int index = 0;
    for (int y = 0; y < height - 1; ++y) {
        for (int x = 0; x < width - 1; ++x) {
            indices[index++] = y * width + x;
            indices[index++] = (y + 1) * width + x;
            indices[index++] = y * width + x + 1;
            indices[index++] = y * width + x + 1;
            indices[index++] = (y + 1) * width + x;
            indices[index++] = (y + 1) * width + x + 1;
        }
    }

    FreeImage_Unload(dib);

    // Generate VAO, VBO, and EBO
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, width * height * 3 * sizeof(float), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (width - 1) * (height - 1) * 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

    // Specify the layout of the vertex data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Vertex normals
    //glGenBuffers(1, &vboNormals);
    //glBindBuffer(GL_ARRAY_BUFFER, vboNormals);
    //glBufferData(GL_ARRAY_BUFFER, width * height * 3 * sizeof(float), normals, GL_STATIC_DRAW);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)(width * height * 6 * sizeof(float)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void TerrainComponent::draw(float deltaTime)
{
    glBindVertexArray(vao);
    //glBindTexture(GL_TEXTURE_2D, texture);

    Hierarchy& hierarchy = Hierarchy::getInstance();
    GLint ambientColorLoc = glGetUniformLocation(Hierarchy::getInstance().getShaders().at(0), "ambientColor");
    CameraComponent* camComp = (CameraComponent*)hierarchy.getActiveCamera()->findComponentsByType("CameraComponent").at(0);
    glUniform3f(ambientColorLoc, camComp->getAmbientLight().x, camComp->getAmbientLight().y, camComp->getAmbientLight().z);

    glm::mat4 model = glm::mat4(1.0f);
    int modelIndex = glGetUniformLocation(hierarchy.getShaders()[0], "model");
    glUniformMatrix4fv(modelIndex, 1, GL_FALSE, glm::value_ptr(model));

    glUniformMatrix4fv(glGetUniformLocation(Hierarchy::getInstance().getShaders().at(0), "view"), 1, GL_FALSE, glm::value_ptr(camComp->getView()));
    glUniformMatrix4fv(glGetUniformLocation(Hierarchy::getInstance().getShaders().at(0), "projection"), 1, GL_FALSE, glm::value_ptr(camComp->getProjection()));

    //glActiveTexture(GL_TEXTURE0);
    glUniform1i(glGetUniformLocation(Hierarchy::getInstance().getShaders().at(0), "texture_diffuse1"), 0);
    glBindTexture(GL_TEXTURE_2D, texture);
    // and finally bind the texture

    SkyboxComponent* camSky = (SkyboxComponent*)hierarchy.getActiveCamera()->findComponentsByType("SkyboxComponent").at(0);
    if (camSky) {
        GLint lightDirectionLoc = glGetUniformLocation(Hierarchy::getInstance().getShaders().at(0), "lightDirection");
        glUniform3f(lightDirectionLoc, camSky->getSunDirection().x, camSky->getSunDirection().y, camSky->getSunDirection().z);
        GLint lightColorLoc = glGetUniformLocation(Hierarchy::getInstance().getShaders().at(0), "lightColor");
        glUniform3f(lightColorLoc, camSky->getSunColor().x, camSky->getSunColor().y, camSky->getSunColor().z);
    }

    glDrawElements(GL_TRIANGLES, (width - 1) * (height - 1) * 6, GL_UNSIGNED_INT, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
}

void TerrainComponent::createPhysics()
{
    Hierarchy& hierarchy = Hierarchy::getInstance();
    btDiscreteDynamicsWorld* dynamicsWorld = hierarchy.getDynamicsWorld();
    if (!dynamicsWorld) {
        throw std::runtime_error("DynamicsWorld is not initialized.");
    }

    // Create a static terrain shape
    btScalar newMargin = 10.1;
    btHeightfieldTerrainShape* terrainShape = new btHeightfieldTerrainShape(width, height, vertices, 1.0f, 0.0f, heightScale, 1, PHY_FLOAT, false);
    terrainShape->setMargin(newMargin);

    // Create motion state
    btDefaultMotionState* motionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 0)));

    // Create rigid body
    btRigidBody::btRigidBodyConstructionInfo rbInfo(0, motionState, terrainShape, btVector3(0, 0, 0));
    btRigidBody* rigidBody = new btRigidBody(rbInfo);

    //btStaticPlaneShape* planeShape = new btStaticPlaneShape(btVector3(0, 1, 0), 0);
    //planeShape->setMargin(newMargin);
    //btDefaultMotionState* motionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 50, 0)));
    //btRigidBody::btRigidBodyConstructionInfo rbInfo(0, motionState, planeShape);
    //btRigidBody* rigidBody = new btRigidBody(rbInfo);


    // Add the rigid body to the dynamicsWorld
    dynamicsWorld->addRigidBody(rigidBody);
}

void TerrainComponent::loadTexture(const char* texturePath)
{
    glBindVertexArray(vao);
    // Load the texture using FreeImage
    FREE_IMAGE_FORMAT fif = FreeImage_GetFileType(texturePath, 0);
    if (fif == FIF_UNKNOWN)
        fif = FreeImage_GetFIFFromFilename(texturePath);

    if (fif == FIF_UNKNOWN)
        throw std::runtime_error("Unsupported texture format");

    FIBITMAP* textureDib = FreeImage_Load(fif, texturePath);
    if (!textureDib)
        throw std::runtime_error("Failed to load texture image");

    // Generate and bind the texture
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // Set the texture parameters (you may need to adjust these based on your requirements)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Load the texture data
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, FreeImage_GetWidth(textureDib), FreeImage_GetHeight(textureDib), 0,
        GL_RGB, GL_UNSIGNED_BYTE, FreeImage_GetBits(textureDib));

    // Generate VAO, VBO, and EBO
    // ... (existing code)

    // Generate and bind the VBO for texture coordinates
    GLuint textureVBO;
    glGenBuffers(1, &textureVBO);
    glBindBuffer(GL_ARRAY_BUFFER, textureVBO);
    glBufferData(GL_ARRAY_BUFFER, width * height * 2 * sizeof(float), textureCoords, GL_STATIC_DRAW);

    // Specify the layout of the texture coordinate data
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(2);

    // Unbind the VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Unbind the VAO
    glBindVertexArray(0);

    FreeImage_Unload(textureDib);
}
