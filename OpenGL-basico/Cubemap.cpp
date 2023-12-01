#include "Cubemap.h"

Cubemap::Cubemap()
{
}

GLuint Cubemap::loadCubemap(std::vector<const char*> faces)
{
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);

    int width, height, nrChannels;
    for (GLuint i = 0; i < faces.size(); i++) {
        FIBITMAP* image = FreeImage_Load(FIF_JPEG, faces[i], JPEG_DEFAULT);

        if (!image) {
            std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
            continue;
        }

        width = FreeImage_GetWidth(image);
        height = FreeImage_GetHeight(image);
        nrChannels = FreeImage_GetBPP(image) / 8;

        // Note: FreeImage loads images with the origin at the top-left, but OpenGL expects the bottom-left origin.
        // You might need to flip the image vertically depending on your requirements.

        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, FreeImage_GetBits(image));

        FreeImage_Unload(image);
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    // Set up the VAO and VBO for the skybox cube
float skyboxVertices[] = {
    // positions
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    -1.0f,  1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f,  1.0f
};

    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);

    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);

    // Set the vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return textureId;
}

void Cubemap::draw()
{
    /*
    //glDepthFunc(GL_LEQUAL);
    glDepthMask(GL_FALSE);
    GLuint shaderProgram = Hierarchy::getInstance().getShaders().at(1);
    glUseProgram(shaderProgram);  // Use your shader program for the skybox

    // Get the active camera from your Hierarchy singleton
    Entity* activeCamera = Hierarchy::getInstance().getActiveCamera();

    // Construct the view matrix manually using camera components
    CameraComponent* cam = (CameraComponent*) activeCamera->findComponentsByType("CameraComponent").at(0);
    glm::mat4 view = glm::translate(glm::mat4(1.0), -cam->getTransform()->getPosition()); // Translate
    view = glm::rotate(view, glm::radians(cam->getPitch()), glm::vec3(1, 0, 0)); // Rotate around X-axis
    view = glm::rotate(view, glm::radians(cam->getYaw()), glm::vec3(0, 1, 0));  // Rotate around Y-axis
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -1.0f));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));

    glm::mat4 projection = glm::perspective(cam->getFOV(), 4.0f / 3.0f, 1.0f, 10000.f);
    CameraComponent* camComp = (CameraComponent*)Hierarchy::getInstance().getActiveCamera()->findComponentsByType("CameraComponent").at(0);
    projection = glm::rotate(projection, glm::radians(camComp->getPitch()), glm::vec3(1.0f, 0.0f, 0.0f));
    projection = glm::rotate(projection, glm::radians(camComp->getYaw()), glm::vec3(0.0f, 1.0f, 0.0f));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    glUniform1i(glGetUniformLocation(shaderProgram, "skybox"), 0);

    glBindVertexArray(skyboxVAO);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);

    glDrawArrays(GL_TRIANGLES, 0, 36); // Assuming you have a VAO with cube vertices

    glBindVertexArray(0);

    GLuint defaultShader = Hierarchy::getInstance().getShaders().at(0);
    glUseProgram(defaultShader);
    //glDepthFunc(GL_LESS);
    glDepthMask(GL_TRUE);
    */

    glDepthMask(GL_FALSE);
    GLuint shaderProgram = Hierarchy::getInstance().getShaders().at(1);
    glUseProgram(shaderProgram);

    // ... set view and projection matrix
    Entity* activeCamera = Hierarchy::getInstance().getActiveCamera();
    CameraComponent* cam = (CameraComponent*)activeCamera->findComponentsByType("CameraComponent").at(0);
    glm::vec3 right = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), cam->getViewDirection()));
    glm::vec3 up = glm::normalize(glm::cross(cam->getViewDirection(), right));
    glm::mat4 view(1.0);
    //glm::mat4 view = glm::translate(glm::mat4(1.0), cam->getTransform()->getPosition()); // Translate
    //view = glm::rotate(view, glm::radians(cam->getPitch()), glm::vec3(1, 0, 0)); // Rotate around X-axis
    //view = glm::rotate(view, glm::radians(cam->getYaw()), glm::vec3(0, 1, 0));  // Rotate around Y-axis
    //glm::mat4 view = glm::lookAt(cam->getTransform()->getPosition(), cam->getTransform()->getPosition() + cam->getViewDirection(), up);
    glm::mat4 projection = glm::perspective(cam->getFOV(), 4.0f / 3.0f, 0.1f, 10000.f);
    projection = glm::rotate(projection, glm::radians(cam->getPitch()), glm::vec3(1.0f, 0.0f, 0.0f));
    projection = glm::rotate(projection, glm::radians(cam->getYaw()), glm::vec3(0.0f, 1.0f, 0.0f));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    glUniform1i(glGetUniformLocation(shaderProgram, "skybox"), 0);

    glBindVertexArray(skyboxVAO);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glDepthMask(GL_TRUE);
    GLuint defaultShader = Hierarchy::getInstance().getShaders().at(0);
    glUseProgram(defaultShader);
}
