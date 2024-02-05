#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#include "Gui.hpp"
#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h>

#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

#ifdef __EMSCRIPTEN__
#include "../libs/emscripten/emscripten_mainloop_stub.h"
#endif

// Error handling and callback functions
static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

//########################### Initialization functions ########################
static bool initializeWindow(const char* glsl_version, GLFWwindow** outWindow) {
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW." << std::endl;
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    *outWindow = glfwCreateWindow(1280, 720, "Database Crawler", NULL, NULL);
    if (*outWindow == NULL) {
        std::cerr << "Failed to create GLFW window." << std::endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(*outWindow);
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        fprintf(stderr, "GLEW Error: %s\n", glewGetErrorString(err));
        glfwDestroyWindow(*outWindow);
        glfwTerminate();
        return false;
    }

    glfwSwapInterval(1); // Enable vsync
    return true;
}

bool setupImGui(GLFWwindow* window, const char* glsl_version,  ImGuiIO* io) {
    // Check for valid window pointer
    if (!window) {
        std::cerr << "setupImGui: Provided GLFWwindow pointer is null." << std::endl;
        return false;
    }

    // Initialize ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    *io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();

    if (!ImGui_ImplGlfw_InitForOpenGL(window, true)) {
        std::cerr << "Failed to initialize ImGui GLFW." << std::endl;
        return false;
    }
    if (!ImGui_ImplOpenGL3_Init(glsl_version)) {
        std::cerr << "Failed to initialize ImGui OpenGL." << std::endl;
        return false;
    }

    return true;
}

// ########################### Cleanup function ###########################
void cleanup(GLFWwindow* window)
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    if (window) {
        glfwDestroyWindow(window);
    }
    glfwTerminate();
}

// ########################### Utility functions ###########################
void renderMenuBar()
{
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("Connections")) {
            if (ImGui::MenuItem("Connection 1")) { /* ... */ }
            if (ImGui::MenuItem("Connection 2")) { /* ... */ }
            if (ImGui::MenuItem("Connection 3")) { /* ... */ }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

void renderBackground(ImVec2 windowSize, GLuint backgroundTextureID)
{

    //render background image
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::Begin("##Background", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoInputs);
    ImGui::SetWindowPos(ImVec2(0, 0), ImGuiCond_Always);
    ImGui::SetWindowSize(windowSize, ImGuiCond_Always);
    ImGui::Image(reinterpret_cast<void*>(static_cast<intptr_t>(backgroundTextureID)), windowSize);
    ImGui::End();
    ImGui::PopStyleVar();
}

// ########################### MainLoop ###########################
bool mainLoop(GLFWwindow* window, ImGuiIO* io, GLuint backgroundTextureID, T_data* params)
{
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Fetch the new window size
        ImVec2 windowSize = ImGui::GetIO().DisplaySize;

        //set params to render
        renderBackground(windowSize, backgroundTextureID);
        renderMenuBar();
        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }
    //TODO: CHeck for errors here
    return (EXIT_SUCCESS);
}

// ########################### Main app ###########################
int appGui(T_data& params)
{
    ImGuiIO io;
    // Create window with graphics context
    const char* glsl_version = "#version 130";
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls

    GLFWwindow* window;
    if (!initializeWindow(glsl_version, &window))
    {
        std::cerr << "Shutdown App." << std::endl;
        //TODO: Try recover and restart.
        return (-1);
    }
    GLuint backgroundTextureID = loadImage(_THUB_PATH, window);
    if (backgroundTextureID == 0) {
        // Handle the error, maybe exit the application
        std::cerr << "Failed to load the background texture." << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return (-1);
    }

    // Setup ImGui binding
    if (!setupImGui(window, glsl_version, &io))
    {
        std::cerr << "Failed to setup ImGui." << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }
    if (mainLoop(window, &io, backgroundTextureID, &params))
    {
        std::cerr << "An error occurred during the main loop." << std::endl;
        cleanup(window);
        return (EXIT_FAILURE);
    }
    // Cleanup
    cleanup(window);
    return (EXIT_SUCCESS);
}
