#include "AppGui.hpp"

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
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
        //set params to render
        params->renderSelected(windowSize);
        params->renderMenuBar();
        ImGui::End();
        ImGui::PopStyleVar();
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
    return EXIT_SUCCESS;
}

// ########################### Main app (Init & cleanup) ###########################
int initGui(T_data& params)
{
    //init window && io && textures
    if (params.initImgui())
        return (EXIT_FAILURE);

    // Setup ImGui binding
    if (!params.setupImGui())
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
