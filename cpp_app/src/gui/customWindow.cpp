#include "Macros.hpp"
#include "imgui.h"
#include "Gui.hpp"
#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif
#include "stb_image.h"

GLuint loadImage(const char* imagePath, GLFWwindow* window)
{
    // Load the image using stb_image
    int width, height, channels;
    unsigned char* data = stbi_load(imagePath, &width, &height, &channels, 4);
    if (data == nullptr) {
        std::cerr << "Failed to load image: " << imagePath << std::endl;
        return 0;
    }
    // Create a texture
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Set the texture wrapping and filtering options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Load the texture data
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cerr << "OpenGL Error after glGenerateMipmap: " << error << std::endl;
    }
    // Free the image memory and unbind the texture
    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);

    return textureID;
}

void showDatabaseConfigWindow(Macros& params)
{
    static char dbHost[255] = "";
    static char dbName[255] = "";
    static char dbUser[255] = "";
    static char dbPass[255] = "";
    static int dbPort = 0;

    ImGui::Begin("Database Configuration");

    ImGui::InputText("Host", dbHost, IM_ARRAYSIZE(dbHost));
    ImGui::InputText("Database Name", dbName, IM_ARRAYSIZE(dbName));
    ImGui::InputText("User", dbUser, IM_ARRAYSIZE(dbUser));
    ImGui::InputText("Password", dbPass, IM_ARRAYSIZE(dbPass));
    ImGui::InputInt("Port", &dbPort);

    if (ImGui::Button("Connect")) {
        params.setDatabaseHost(dbHost);
        params.setDatabaseName(dbName);
        params.setUsername(dbUser);
        params.setPassword(dbPass);
        params.setDatabasePort(dbPort);

        if (params.connectToDatabase()) {
            std::cout << "Connection established!" << std::endl;
        } else {
            std::cout << "Failed to connect to the database." << std::endl;
        }
    }

    ImGui::End();
}