#include "TerrainComponent.h"

TerrainComponent::TerrainComponent() : EntityComponent("TerrainComponent")
{
}

TerrainComponent::~TerrainComponent()
{
    delete[] vertices;
    delete[] indices;

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
}

void TerrainComponent::loadHeightmap(const char* filePath, float scale)
{
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

    // Generate vertices and indices
    // Adjust scale if needed
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            unsigned int index = (y * width + x) * 3;
            RGBQUAD color;
            FreeImage_GetPixelColor(dib, x, y, &color);

            vertices[index] = x * scale;
            vertices[index + 1] = color.rgbRed * scale;
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

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void TerrainComponent::draw()
{
    glBindVertexArray(vao);
    glBindTexture(GL_TEXTURE_2D, texture);
    glDrawElements(GL_TRIANGLES, (width - 1) * (height - 1) * 6, GL_UNSIGNED_INT, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
}

void TerrainComponent::loadTexture(const char* texturePath)
{
    // Load the texture using FreeImage
    FREE_IMAGE_FORMAT fif = FreeImage_GetFileType(texturePath, 0);
    if (fif == FIF_UNKNOWN)
        fif = FreeImage_GetFIFFromFilename(texturePath);

    if (fif == FIF_UNKNOWN)
        throw std::runtime_error("Unsupported texture format");

    FIBITMAP* textureDib = FreeImage_Load(fif, texturePath);
    if (!textureDib)
        throw std::runtime_error("Failed to load texture image");

    // Allocate memory for texture coordinates
    textureCoords = new float[width * height * 2];

    // Generate texture coordinates
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            unsigned int index = (y * width + x) * 2;
            textureCoords[index] = static_cast<float>(x) / (width - 1);
            textureCoords[index + 1] = static_cast<float>(y) / (height - 1);
        }
    }

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
        GL_BGR, GL_UNSIGNED_BYTE, FreeImage_GetBits(textureDib));

    // Generate VAO, VBO, and EBO
    // ... (existing code)

    // Generate and bind the VBO for texture coordinates
    GLuint textureVBO;
    glGenBuffers(1, &textureVBO);
    glBindBuffer(GL_ARRAY_BUFFER, textureVBO);
    glBufferData(GL_ARRAY_BUFFER, width * height * 2 * sizeof(float), textureCoords, GL_STATIC_DRAW);

    // Specify the layout of the texture coordinate data
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);

    // Unbind the VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Unbind the VAO
    glBindVertexArray(0);

    FreeImage_Unload(textureDib);
}
