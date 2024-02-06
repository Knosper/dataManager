#include "AppGui.hpp"

//########################### Initialization functions ########################


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

// ########################### MenuBar Buttons ###########################
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
                params.setCurrentMenuItem(SelectedMenuItem::ListDatabases);
                std::cout << "List all detected databases" << std::endl;
            }
            ImGui::Image((void*)(intptr_t)params.getIconTextureID(_ICON_NEW_CONNECTION), ImVec2(18, 18)); 
            ImGui::SameLine();
            if (ImGui::MenuItem("New Connection"))
            {
                params.setCurrentMenuItem(SelectedMenuItem::NewConnection);
                std::cout << "Open the 'New Connection' Input window" << std::endl;
            }
            ImGui::Image((void*)(intptr_t)params.getIconTextureID(_ICON_MANAGE_CONNECTION), ImVec2(18, 18)); 
            ImGui::SameLine();
            if (ImGui::MenuItem("Manage Connections"))
            {
                params.setCurrentMenuItem(SelectedMenuItem::ManageConnections);
                std::cout << "Open the 'Manage Connections' window" << std::endl;
            }
            ImGui::Image((void*)(intptr_t)params.getIconTextureID(_ICON_DATABASE_IMPORT), ImVec2(18, 18)); 
            ImGui::SameLine();
            if (ImGui::MenuItem("Import Connection"))
            {
                params.setCurrentMenuItem(SelectedMenuItem::ImportConnection);
                std::cout << "Open the 'Import Connection' window" << std::endl;
            }
            ImGui::Image((void*)(intptr_t)params.getIconTextureID(_ICON_DATABASE_EXPORT), ImVec2(18, 18)); 
            ImGui::SameLine();
            if (ImGui::MenuItem("Export Connection"))
            {
                params.setCurrentMenuItem(SelectedMenuItem::ExportConnection);
                std::cout << "Open the 'Export Connection' window" << std::endl;
            }
            ImGui::Image((void*)(intptr_t)params.getIconTextureID(_ICON_CREATE_DATABASE), ImVec2(18, 18)); 
            ImGui::SameLine();
            if (ImGui::MenuItem("Create Database"))
            {
                params.setCurrentMenuItem(SelectedMenuItem::CreateDatabase);
                std::cout << "Open the 'Create Database' window" << std::endl;
            }
            ImGui::Image((void*)(intptr_t)params.getIconTextureID(_ICON_DELETE_DATABASE), ImVec2(18, 18)); 
            ImGui::SameLine();
            if (ImGui::MenuItem("Delete Database"))
            {
                params.setCurrentMenuItem(SelectedMenuItem::DeleteDatabase);
                std::cout << "Open the 'Delete Database' window" << std::endl;
            }
            ImGui::Image((void*)(intptr_t)params.getIconTextureID(_ICON_DATABASE_BACKUP), ImVec2(18, 18)); 
            ImGui::SameLine();
            if (ImGui::MenuItem("Backup Database"))
            {
                params.setCurrentMenuItem(SelectedMenuItem::BackupDatabase);
                std::cout << "Open the 'Backup Database' window" << std::endl;
            }
            ImGui::Image((void*)(intptr_t)params.getIconTextureID(_ICON_RESTORE), ImVec2(18, 18)); 
            ImGui::SameLine();
            if (ImGui::MenuItem("Restore Database"))
            {
                params.setCurrentMenuItem(SelectedMenuItem::RestoreDatabase);
                std::cout << "Open the 'Restore Database' window" << std::endl;
            }
            ImGui::EndMenu();
        }
        ImGui::Image((void*)(intptr_t)params.getIconTextureID(_ICON_TOOLS), ImVec2(18, 18)); 
        ImGui::SameLine();
        if (ImGui::BeginMenu("Tools"))
        {
            ImGui::Image((void*)(intptr_t)params.getIconTextureID(_ICON_VISUALIZE_DATABASE), ImVec2(18, 18)); 
            ImGui::SameLine();
            if (ImGui::MenuItem("Visualize Database"))
            {
                params.setCurrentMenuItem(SelectedMenuItem::VisualizeDatabase);
                std::cout << "Open the 'Visualize Database' window" << std::endl;
            }
            ImGui::Image((void*)(intptr_t)params.getIconTextureID(_ICON_DATABASE_LOGS), ImVec2(18, 18)); 
            ImGui::SameLine();
            if (ImGui::MenuItem("Database Logs"))
            {
                params.setCurrentMenuItem(SelectedMenuItem::DatabaseLogs);
                std::cout << "Open the 'Database Logs' window" << std::endl;
            }
            ImGui::EndMenu();
        }
        ImGui::Image((void*)(intptr_t)params.getIconTextureID(_ICON_SETTINGS), ImVec2(18, 18)); 
        ImGui::SameLine();
        if (ImGui::BeginMenu("Settings"))
        {
            ImGui::Image((void*)(intptr_t)params.getIconTextureID(_ICON_PREFERENCES), ImVec2(18, 18)); 
            ImGui::SameLine();
            if (ImGui::MenuItem("Preferences"))
            {
                params.setCurrentMenuItem(SelectedMenuItem::Preferences);
                std::cout << "Open the 'Preferences' window" << std::endl;
            }
            ImGui::Image((void*)(intptr_t)params.getIconTextureID(_ICON_APPERANCE), ImVec2(18, 18)); 
            ImGui::SameLine();
            if (ImGui::MenuItem("Appearance"))
            {
                params.setCurrentMenuItem(SelectedMenuItem::Appearance);
                std::cout << "Open the 'Appearance' window" << std::endl;
            }
            ImGui::EndMenu();
        }
        ImGui::Image((void*)(intptr_t)params.getIconTextureID(_ICON_HELP), ImVec2(18, 18)); 
        ImGui::SameLine();
        if (ImGui::BeginMenu("Help"))
        {
            ImGui::Image((void*)(intptr_t)params.getIconTextureID(_ICON_DOCS), ImVec2(18, 18)); 
            ImGui::SameLine();
            if (ImGui::MenuItem("Docs"))
            {
                params.setCurrentMenuItem(SelectedMenuItem::Docs);
                std::cout << "Open the 'Docs' window" << std::endl;
            }
            ImGui::Image((void*)(intptr_t)params.getIconTextureID(_ICON_UPDATE), ImVec2(18, 18)); 
            ImGui::SameLine();
            if (ImGui::MenuItem("Check for Updates"))
            {
                params.setCurrentMenuItem(SelectedMenuItem::CheckForUpdates);
                std::cout << "Open the 'Check for Updates' window" << std::endl;
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

void setStyle() {
    ImGuiStyle& style = ImGui::GetStyle();

    // Adjusting window rounding to make the UI look more sleek
    style.WindowRounding = 5.0f;

    // Padding
    style.FramePadding = ImVec2(5, 5);
    style.ItemSpacing = ImVec2(10, 10);

    // Colors
    ImVec4* colors = style.Colors;
    colors[ImGuiCol_Text] = ImVec4(0.95f, 0.96f, 0.98f, 1.00f);
    colors[ImGuiCol_WindowBg] = ImVec4(0.18f, 0.22f, 0.25f, 1.00f);
    colors[ImGuiCol_Button] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.25f, 0.30f, 0.35f, 1.00f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.30f, 0.35f, 0.40f, 1.00f);
    // Add more color settings as needed...
}

// Call this function where you want to render the search options in the main window
void renderSearchOptions(T_data* params, ImVec2 windowSize)
{
    ImGui::Begin("##DatabaseList", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
    ImGui::SetWindowPos(ImVec2(0, 20), ImGuiCond_Always);
    ImGui::SetWindowSize(windowSize, ImGuiCond_Always);
    if (!params) return; // Ensure that params is not a null pointer

    // Check the current selected menu item
    if (params->getCurrentMenuItem() == SelectedMenuItem::ListDatabases) {
        // Text Input for database name
        static char dbName[128] = "";
        ImGui::InputText("Database Name", dbName, IM_ARRAYSIZE(dbName));

        // Numeric input fields for specifying size range
        static int minSize = 0;
        ImGui::InputInt("Min Size", &minSize);
        ImGui::SameLine(); // Place next item on the same line
        static int maxSize = 100;
        ImGui::InputInt("Max Size", &maxSize);

        // Dropdown menu for database type selection
        static const char* dbTypes[] = {"Type 1", "Type 2", "Type 3"};
        static int currentDbTypeIndex = 0;
        if (ImGui::BeginCombo("Database Type", dbTypes[currentDbTypeIndex])) {
            for (int i = 0; i < IM_ARRAYSIZE(dbTypes); i++) {
                bool isSelected = (currentDbTypeIndex == i);
                if (ImGui::Selectable(dbTypes[i], isSelected))
                    currentDbTypeIndex = i;
                if (isSelected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndCombo();
        }

        // Checkboxes for additional options
        static bool option1 = false;
        ImGui::Checkbox("Option 1", &option1);
        ImGui::SameLine(); // Align next item on the same line
        static bool option2 = false;
        ImGui::Checkbox("Option 2", &option2);

        // Buttons for actions
        if (ImGui::Button("Search")) {
            // Execute search logic using the parameters
        }
        ImGui::SameLine();
        if (ImGui::Button("Reset")) {
            // Reset the search parameters
            dbName[0] = '\0';
            minSize = 0;
            maxSize = 100;
            currentDbTypeIndex = 0;
            option1 = false;
            option2 = false;
        }
    }
}



//complete window background
void renderBackground(ImVec2 windowSize, GLuint backgroundTextureID)
{
    //render background image
    ImGui::Begin("##Background", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoInputs);
    ImGui::SetWindowPos(ImVec2(0, 0), ImGuiCond_Always);
    ImGui::SetWindowSize(windowSize, ImGuiCond_Always);
    ImGui::Image(reinterpret_cast<void*>(static_cast<intptr_t>(backgroundTextureID)), windowSize);
}

void renderSelected(ImVec2 windowSize, T_data* params)
{
    switch (params->getCurrentMenuItem())
    {
        case SelectedMenuItem::StartPage:
        {
            renderBackground(windowSize, params->getBackgroundTextureID());
            break;
        }
        case SelectedMenuItem::ListDatabases:
        {
            renderSearchOptions(params, windowSize);
            break;
        }
        case SelectedMenuItem::NewConnection:
            break;
        case SelectedMenuItem::ManageConnections:
            break;
        case SelectedMenuItem::ImportConnection:
            break;
        case SelectedMenuItem::ExportConnection:
            break;
        case SelectedMenuItem::CreateDatabase:
            break;
        case SelectedMenuItem::DeleteDatabase:
            break;
        case SelectedMenuItem::BackupDatabase:
            break;
        case SelectedMenuItem::RestoreDatabase:
            break;
        case SelectedMenuItem::VisualizeDatabase:
            break;
        case SelectedMenuItem::DatabaseLogs:
            break;
        case SelectedMenuItem::Preferences:
            break;
        case SelectedMenuItem::Appearance:
            break;
        case SelectedMenuItem::Docs:
            break;
        case SelectedMenuItem::CheckForUpdates:
            break;
        default:
        {
            renderBackground(windowSize, params->getBackgroundTextureID());
            break;
        }
    }
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
        renderSelected(windowSize, params);
        renderMenuBar(*params);
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
