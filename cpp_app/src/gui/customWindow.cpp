#include "tData.hpp"
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

void showDatabaseConfigWindow(T_data& params)
{
    /*static char dbHost[255] = "";
    strncpy(dbHost, params.getDatabaseHost().c_str(), sizeof(dbHost) - 1);
    dbHost[sizeof(dbHost) - 1] = '\0';
    static char dbName[255] = "";
    strncpy(dbName, params.getDatabaseName().c_str(), sizeof(dbName) - 1);
    dbName[sizeof(dbName) - 1] = '\0';
    static char dbUser[255] = "";
    strncpy(dbUser, params.getUsername().c_str(), sizeof(dbUser) - 1);
    dbUser[sizeof(dbUser) - 1] = '\0';
    static char dbPass[255] = "";
    strncpy(dbPass, params.getPassword().c_str(), sizeof(dbPass) - 1);
    dbPass[sizeof(dbPass) - 1] = '\0';
    static int dbPort = params.getDatabasePort();*/

    static char dbHost[255] = "";
    static char dbName[255] = "";
    static char dbUser[255] = "";
    static char dbPass[255] = "";
    static int dbPort = 0;
    // Get the main window's position and size
    int main_window_x, main_window_y;
    int main_window_width, main_window_height;
    glfwGetWindowPos(params.getWindow(), &main_window_x, &main_window_y);
    glfwGetWindowSize(params.getWindow(), &main_window_width, &main_window_height);

    // Set the position of the database config window within the boundaries
    ImGui::SetNextWindowPos(ImVec2(main_window_x, main_window_y), ImGuiCond_FirstUseEver, ImVec2(0, 0));
    ImGui::SetNextWindowSizeConstraints(ImVec2(300, 200), ImVec2(main_window_width, main_window_height));

    // Begin the window
    ImGui::Begin("Init Database", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize);


    // Input fields with labels
    ImGui::InputText("Host", dbHost, IM_ARRAYSIZE(dbHost));
    ImGui::InputText("Database Name", dbName, IM_ARRAYSIZE(dbName));
    ImGui::InputText("User", dbUser, IM_ARRAYSIZE(dbUser));
    ImGui::InputText("Password", dbPass, IM_ARRAYSIZE(dbPass), ImGuiInputTextFlags_Password);
    ImGui::InputInt("Port", &dbPort);

    // Space between input fields and buttons
    ImGui::Spacing();

    if (ImGui::Button("Connect", ImVec2(ImGui::GetContentRegionAvail().x, 0))) {
        // Attempt to connect to the database and provide feedback
        /*if (attemptDatabaseConnection(params)) {
            ImGui::OpenPopup("Connection Success!");
        } else {
            ImGui::OpenPopup("Connection Failed!");
        }*/
    }

    // Popups for connection feedback
    if (ImGui::BeginPopupModal("Connection Success!", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::Text("Connected to the database successfully.");
        if (ImGui::Button("OK")) { ImGui::CloseCurrentPopup(); }
        ImGui::EndPopup();
    }

    if (ImGui::BeginPopupModal("Connection Failed!", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::Text("Failed to connect to the database.");
        if (ImGui::Button("OK")) { ImGui::CloseCurrentPopup(); }
        ImGui::EndPopup();
    }

    ImGui::End();
}