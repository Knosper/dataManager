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
/*

*/
void renderMenuBar(T_data& params)
{
    if (ImGui::BeginMainMenuBar())
    {
        ImGui::Image((void*)(intptr_t)params.getIconTextureID(_ICON_DATABASE), ImVec2(18, 18)); 
        ImGui::SameLine();
        if (ImGui::BeginMenu("Database"))
        {
            ImGui::Image((void*)(intptr_t)params.getIconTextureID(_ICON_LIST_DATABASE), ImVec2(18, 18)); 
            ImGui::SameLine();
            if (ImGui::MenuItem("List Databases"))
            {
                std::cout << "List all detected databases" << std::endl;
            }
            ImGui::Image((void*)(intptr_t)params.getIconTextureID(_ICON_NEW_CONNECTION), ImVec2(18, 18)); 
            ImGui::SameLine();
            if (ImGui::MenuItem("New Connection"))
            {
                std::cout << "Open the 'New Connection' Input window" << std::endl;
            }
            ImGui::Image((void*)(intptr_t)params.getIconTextureID(_ICON_MANAGE_CONNECTION), ImVec2(18, 18)); 
            ImGui::SameLine();
            if (ImGui::MenuItem("Manage Connections")) { /* ... */ }
            ImGui::Image((void*)(intptr_t)params.getIconTextureID(_ICON_DATABASE_IMPORT), ImVec2(18, 18)); 
            ImGui::SameLine();
            if (ImGui::MenuItem("Import Connection")) { /* ... */ }
            ImGui::Image((void*)(intptr_t)params.getIconTextureID(_ICON_DATABASE_EXPORT), ImVec2(18, 18)); 
            ImGui::SameLine();
            if (ImGui::MenuItem("Export Connection")) { /* ... */ }
            ImGui::Image((void*)(intptr_t)params.getIconTextureID(_ICON_CREATE_DATABASE), ImVec2(18, 18)); 
            ImGui::SameLine();
            if (ImGui::MenuItem("Create Database")) { /* ... */ }
            ImGui::Image((void*)(intptr_t)params.getIconTextureID(_ICON_DELETE_DATABASE), ImVec2(18, 18)); 
            ImGui::SameLine();
            if (ImGui::MenuItem("Delete Database")) { /* ... */ }
            ImGui::Image((void*)(intptr_t)params.getIconTextureID(_ICON_DATABASE_BACKUP), ImVec2(18, 18)); 
            ImGui::SameLine();
            if (ImGui::MenuItem("Backup Database")) { /* ... */ }
            ImGui::Image((void*)(intptr_t)params.getIconTextureID(_ICON_RESTORE), ImVec2(18, 18)); 
            ImGui::SameLine();
            if (ImGui::MenuItem("Restore Database")) { /* ... */ }
            ImGui::EndMenu();
        }
        ImGui::Image((void*)(intptr_t)params.getIconTextureID(_ICON_TOOLS), ImVec2(18, 18)); 
        ImGui::SameLine();
        if (ImGui::BeginMenu("Tools"))
        {
            ImGui::Image((void*)(intptr_t)params.getIconTextureID(_ICON_VISUALIZE_DATABASE), ImVec2(18, 18)); 
            ImGui::SameLine();
            if (ImGui::MenuItem("Visualize Database")) { /* ... */ }
            ImGui::Image((void*)(intptr_t)params.getIconTextureID(_ICON_DATABASE_LOGS), ImVec2(18, 18)); 
            ImGui::SameLine();
            if (ImGui::MenuItem("Database Logs")) { /* ... */ }

            ImGui::EndMenu();
        }
        ImGui::Image((void*)(intptr_t)params.getIconTextureID(_ICON_SETTINGS), ImVec2(18, 18)); 
        ImGui::SameLine();
        if (ImGui::BeginMenu("Settings"))
        {
            ImGui::Image((void*)(intptr_t)params.getIconTextureID(_ICON_PREFERENCES), ImVec2(18, 18)); 
            ImGui::SameLine();
            if (ImGui::MenuItem("Preferences")) { /* ... */ }
            ImGui::Image((void*)(intptr_t)params.getIconTextureID(_ICON_APPERANCE), ImVec2(18, 18)); 
            ImGui::SameLine();
            if (ImGui::MenuItem("Appearance")) { /* ... */ }
            ImGui::EndMenu();
        }
        ImGui::Image((void*)(intptr_t)params.getIconTextureID(_ICON_HELP), ImVec2(18, 18)); 
        ImGui::SameLine();
        if (ImGui::BeginMenu("Help"))
        {
            ImGui::Image((void*)(intptr_t)params.getIconTextureID(_ICON_DOCS), ImVec2(18, 18)); 
            ImGui::SameLine();
            if (ImGui::MenuItem("Docs")) { /* ... */ }
            ImGui::Image((void*)(intptr_t)params.getIconTextureID(_ICON_UPDATE), ImVec2(18, 18)); 
            ImGui::SameLine();
            if (ImGui::MenuItem("Check for Updates")) { /* ... */ }
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

int loadIcons(T_data* params)
{
    params->addIconTextureID(_ICON_APPERANCE, loadImage(_ICON_APPERANCE, params->getWindow()));
    params->addIconTextureID(_ICON_DATABASE_BACKUP, loadImage(_ICON_DATABASE_BACKUP, params->getWindow()));
    params->addIconTextureID(_ICON_BUG, loadImage(_ICON_BUG, params->getWindow()));
    params->addIconTextureID(_ICON_CREATE_DATABASE, loadImage(_ICON_CREATE_DATABASE, params->getWindow()));
    params->addIconTextureID(_ICON_DATABASE_LOGS, loadImage(_ICON_DATABASE_LOGS, params->getWindow()));
    params->addIconTextureID(_ICON_DATABASE, loadImage(_ICON_DATABASE, params->getWindow()));
    params->addIconTextureID(_ICON_DELETE_DATABASE, loadImage(_ICON_DELETE_DATABASE, params->getWindow()));
    params->addIconTextureID(_ICON_DOCS, loadImage(_ICON_DOCS, params->getWindow()));
    params->addIconTextureID(_ICON_DATABASE_EXPORT, loadImage(_ICON_DATABASE_EXPORT, params->getWindow()));
    params->addIconTextureID(_ICON_HELP, loadImage(_ICON_HELP, params->getWindow()));
    params->addIconTextureID(_ICON_DATABASE_IMPORT, loadImage(_ICON_DATABASE_IMPORT, params->getWindow()));
    params->addIconTextureID(_ICON_LIST_DATABASE, loadImage(_ICON_LIST_DATABASE, params->getWindow()));
    params->addIconTextureID(_ICON_MANAGE_CONNECTION, loadImage(_ICON_MANAGE_CONNECTION, params->getWindow()));
    params->addIconTextureID(_ICON_NEW_CONNECTION, loadImage(_ICON_NEW_CONNECTION, params->getWindow()));
    params->addIconTextureID(_ICON_PREFERENCES, loadImage(_ICON_PREFERENCES, params->getWindow()));
    params->addIconTextureID(_ICON_RESTORE, loadImage(_ICON_RESTORE, params->getWindow()));
    params->addIconTextureID(_ICON_SETTINGS, loadImage(_ICON_SETTINGS, params->getWindow()));
    params->addIconTextureID(_ICON_TOOLS, loadImage(_ICON_TOOLS, params->getWindow()));
    params->addIconTextureID(_ICON_UPDATE, loadImage(_ICON_UPDATE, params->getWindow()));
    params->addIconTextureID(_ICON_VISUALIZE_DATABASE, loadImage(_ICON_VISUALIZE_DATABASE, params->getWindow()));
    if (params->getIconTextureID(_ICON_APPERANCE) == 0 || params->getIconTextureID(_ICON_BUG) == 0 || params->getIconTextureID(_ICON_CREATE_DATABASE) == 0 \
    || params->getIconTextureID(_ICON_DATABASE_LOGS) == 0 || params->getIconTextureID(_ICON_DOCS) == 0 || params->getIconTextureID(_ICON_LIST_DATABASE) == 0 || \
    params->getIconTextureID(_ICON_MANAGE_CONNECTION) == 0 || params->getIconTextureID(_ICON_NEW_CONNECTION) == 0 || params->getIconTextureID(_ICON_PREFERENCES) == 0 || \
    params->getIconTextureID(_ICON_UPDATE) == 0 || params->getIconTextureID(_ICON_VISUALIZE_DATABASE) == 0 )
    {
        // Handle the error, maybe exit the application
        std::cerr << "Failed to load Icons textures." << std::endl;
        glfwDestroyWindow(params->getWindow());
        glfwTerminate();
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}

// ########################### Main app ###########################
int initGui(T_data& params)
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
    if (backgroundTextureID == 0)
    {
        // Handle the error, maybe exit the application
        std::cerr << "Failed to load the background texture." << std::endl;
        glfwDestroyWindow(params.getWindow());
        glfwTerminate();
        return (EXIT_FAILURE);
    }
    params.setBackgroundTextureID(backgroundTextureID);

    if (loadIcons(&params))
    {
        std::cerr << "Failed to load icons." << std::endl;
        glfwDestroyWindow(params.getWindow());
        glfwTerminate();
        return (EXIT_FAILURE);
    }
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
