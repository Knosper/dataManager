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
static bool initializeWindow(GLFWwindow** outWindow) {
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW." << std::endl;
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    *outWindow = glfwCreateWindow(1280, 720, "Sql-Crawler 🔍", NULL, NULL);
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

bool setupImGui(T_data &params) {
    const char* glsl_version = "#version 130";
    // Check for valid window pointer
    if (!params.getWindow()) {
        std::cerr << "setupImGui: Provided GLFWwindow pointer is null." << std::endl;
        return false;
    }
    // Initialize ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    params.setIo(&(ImGui::GetIO())); (void) params.getIo();
    ImGui::StyleColorsDark();

    if (!ImGui_ImplGlfw_InitForOpenGL(params.getWindow(), true)) {
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
void renderMenuBar(T_data& params)
{
    if (ImGui::BeginMainMenuBar()) {

        //small icon
        ImGui::Image((void*)(intptr_t)params.getIconTextureID(), ImVec2(18, 18));
        // Add some spacing after the icon
        ImGui::SameLine();

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
bool mainLoop(T_data* params)
{
    while (!glfwWindowShouldClose(params->getWindow()))
    {
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Fetch the new window size
        ImVec2 windowSize = ImGui::GetIO().DisplaySize;

        //set params to render
        renderBackground(windowSize, params->getBackgroundTextureID());
        renderMenuBar(*params);
        
        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(params->getWindow(), &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(params->getWindow());
    }
    //TODO: CHeck for errors here
    return (EXIT_SUCCESS);
}

// ########################### Main app ###########################
int appGui(T_data& params)
{
    // Create window with graphics context
    ImGuiIO io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
    GLFWwindow* window;
    if (!initializeWindow(&window))
    {
        std::cerr << "Shutdown App." << std::endl;
        //TODO: Try recover and restart.
        return (-1);
    }
    params.setWindow(window);
    params.setIo(&io);
    // Load BackgroundTexture
    GLuint backgroundTextureID = loadImage(_THUB_PATH, params.getWindow());
    if (backgroundTextureID == 0) {
        // Handle the error, maybe exit the application
        std::cerr << "Failed to load the background texture." << std::endl;
        glfwDestroyWindow(params.getWindow());
        glfwTerminate();
        return (EXIT_FAILURE);
    }
    params.setBackgroundTextureID(backgroundTextureID);

    GLuint iconTextureID = loadImage(_ICON_PATH, params.getWindow());
    if (iconTextureID == 0) {
        // Handle the error, maybe exit the application
        std::cerr << "Failed to load the background texture." << std::endl;
        glfwDestroyWindow(params.getWindow());
        glfwTerminate();
        return (EXIT_FAILURE);
    }
    params.setIconTextureID(iconTextureID);

    // Setup ImGui binding
    if (!setupImGui(params))
    {
        std::cerr << "Failed to setup ImGui." << std::endl;
        glfwDestroyWindow(params.getWindow());
        glfwTerminate();
        return (EXIT_FAILURE);
    }
    if (mainLoop(&params))
    {
        std::cerr << "An error occurred during the main loop." << std::endl;
        cleanup(params.getWindow());
        return (EXIT_FAILURE);
    }
    // Cleanup
    cleanup(params.getWindow());
    return (EXIT_SUCCESS);
}
