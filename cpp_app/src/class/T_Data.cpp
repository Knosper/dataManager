#include "T_Data.hpp"
#include "DatabaseCrawler.hpp"
#include "utils.hpp"
/* Do this:
      #define STB_IMAGE_IMPLEMENTATION
   before you include this file (stb_image.h) in *one* C or C++ file to create the implementation.*/
#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif
#include "stb_image.h"



T_data::T_data():_backgroundTextureID(), _iconTextureIDs(), _window(), _io(), _currentMenuItem(SelectedMenuItem::StartPage)
{
    std::cout << "default T_data created" << std::endl;
}

T_data::~T_data()
{
    for (auto& pair : this->_iconTextureIDs)
    {
        GLuint textureID = pair.second;
        glDeleteTextures(1, &textureID);
    }
    glDeleteTextures(1, &this->_backgroundTextureID);
    std::cout << "T_data deleted" << std::endl;
}

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

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

int T_data::initImgui()
{
    // Create window with graphics context
    ImGuiIO io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
    GLFWwindow* window;
    if (!initializeWindow(&window))
    {
        std::cerr << "Shutdown App." << std::endl;
        //TODO: Try recover and restart.
        return (EXIT_FAILURE);
    }
    this->setWindow(window);
    this->setIo(&io);
        // Load BackgroundTexture
    GLuint backgroundTextureID = this->loadImage(_THUB_PATH);
    if (backgroundTextureID == 0)
    {
        // Handle the error, maybe exit the application
        std::cerr << "Failed to load the background texture." << std::endl;
        glfwDestroyWindow(this->getWindow());
        glfwTerminate();
        return (EXIT_FAILURE);
    }
    this->setBackgroundTextureID(backgroundTextureID);
    this->loadIcons();

    return (EXIT_SUCCESS);
}

bool T_data::setupImGui()
{
    const char* glsl_version = "#version 130";
    // Check for valid window pointer
    if (!this->getWindow())
    {
        std::cerr << "setupImGui: Provided GLFWwindow pointer is null." << std::endl;
        return false;
    }
    // Initialize ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    this->setIo(&(ImGui::GetIO()));
    ImGui::StyleColorsDark();
    if (!ImGui_ImplGlfw_InitForOpenGL(this->getWindow(), true))
    {
        std::cerr << "Failed to initialize ImGui GLFW." << std::endl;
        return false;
    }
    if (!ImGui_ImplOpenGL3_Init(glsl_version))
    {
        std::cerr << "Failed to initialize ImGui OpenGL." << std::endl;
        return false;
    }
    return true;
}

void T_data::loadIcons()
{
    this->addIconTextureID(_ICON_APPERANCE, loadImage(_ICON_APPERANCE));
    this->addIconTextureID(_ICON_DATABASE_BACKUP, loadImage(_ICON_DATABASE_BACKUP));
    this->addIconTextureID(_ICON_BUG, loadImage(_ICON_BUG));
    this->addIconTextureID(_ICON_CREATE_DATABASE, loadImage(_ICON_CREATE_DATABASE));
    this->addIconTextureID(_ICON_DATABASE_LOGS, loadImage(_ICON_DATABASE_LOGS));
    this->addIconTextureID(_ICON_DATABASE, loadImage(_ICON_DATABASE));
    this->addIconTextureID(_ICON_DELETE_DATABASE, loadImage(_ICON_DELETE_DATABASE));
    this->addIconTextureID(_ICON_DOCS, loadImage(_ICON_DOCS));
    this->addIconTextureID(_ICON_DATABASE_EXPORT, loadImage(_ICON_DATABASE_EXPORT));
    this->addIconTextureID(_ICON_HELP, loadImage(_ICON_HELP));
    this->addIconTextureID(_ICON_DATABASE_IMPORT, loadImage(_ICON_DATABASE_IMPORT));
    this->addIconTextureID(_ICON_LIST_DATABASE, loadImage(_ICON_LIST_DATABASE));
    this->addIconTextureID(_ICON_MANAGE_CONNECTION, loadImage(_ICON_MANAGE_CONNECTION));
    this->addIconTextureID(_ICON_NEW_CONNECTION, loadImage(_ICON_NEW_CONNECTION));
    this->addIconTextureID(_ICON_PREFERENCES, loadImage(_ICON_PREFERENCES));
    this->addIconTextureID(_ICON_RESTORE, loadImage(_ICON_RESTORE));
    this->addIconTextureID(_ICON_SETTINGS, loadImage(_ICON_SETTINGS));
    this->addIconTextureID(_ICON_TOOLS, loadImage(_ICON_TOOLS));
    this->addIconTextureID(_ICON_UPDATE, loadImage(_ICON_UPDATE));
    this->addIconTextureID(_ICON_VISUALIZE_DATABASE, loadImage(_ICON_VISUALIZE_DATABASE));
}

GLuint T_data::loadImage(const char* imagePath)
{
    // Load the image using stb_image
    int width, height, channels;
    unsigned char* data = stbi_load(imagePath, &width, &height, &channels, 4);
    if (data == nullptr) {
        std::cerr << "Failed to load image: " << imagePath << std::endl;
        return (0);
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

void T_data::renderSelected(ImVec2 windowSize)
{
    switch (this->getCurrentMenuItem())
    {
        case SelectedMenuItem::StartPage:
        {
            this->renderBackground(windowSize);
            break;
        }
        case SelectedMenuItem::ListDatabases:
        {
            renderSearchOptions(windowSize);
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
            renderBackground(windowSize);
            break;
        }
    }
}

//complete window background
void T_data::renderBackground(ImVec2 windowSize)
{
    //render background image
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::Begin("##Background", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoInputs);
    ImGui::SetWindowPos(ImVec2(0, 0), ImGuiCond_Always);
    ImGui::SetWindowSize(windowSize, ImGuiCond_Always);
    ImGui::Image(reinterpret_cast<void*>(static_cast<intptr_t>(this->_backgroundTextureID)), windowSize);
    ImGui::PopStyleVar(); 
}

void T_data::renderMenuBar()
{
    if (ImGui::BeginMainMenuBar())
    {
        ImGui::Image((void*)(intptr_t)getIconTextureID(_ICON_DATABASE), ImVec2(18, 18)); 
        ImGui::SameLine();
        if (ImGui::BeginMenu("Database"))
        {
            ImGui::Image((void*)(intptr_t)getIconTextureID(_ICON_LIST_DATABASE), ImVec2(18, 18)); 
            ImGui::SameLine();
            if (ImGui::MenuItem("List Databases"))
            {
                setCurrentMenuItem(SelectedMenuItem::ListDatabases);
                std::cout << "List all detected databases" << std::endl;
            }
            ImGui::Image((void*)(intptr_t)getIconTextureID(_ICON_NEW_CONNECTION), ImVec2(18, 18)); 
            ImGui::SameLine();
            if (ImGui::MenuItem("New Connection"))
            {
                setCurrentMenuItem(SelectedMenuItem::NewConnection);
                std::cout << "Open the 'New Connection' Input window" << std::endl;
            }
            ImGui::Image((void*)(intptr_t)getIconTextureID(_ICON_MANAGE_CONNECTION), ImVec2(18, 18)); 
            ImGui::SameLine();
            if (ImGui::MenuItem("Manage Connections"))
            {
                setCurrentMenuItem(SelectedMenuItem::ManageConnections);
                std::cout << "Open the 'Manage Connections' window" << std::endl;
            }
            ImGui::Image((void*)(intptr_t)getIconTextureID(_ICON_DATABASE_IMPORT), ImVec2(18, 18)); 
            ImGui::SameLine();
            if (ImGui::MenuItem("Import Connection"))
            {
                setCurrentMenuItem(SelectedMenuItem::ImportConnection);
                std::cout << "Open the 'Import Connection' window" << std::endl;
            }
            ImGui::Image((void*)(intptr_t)getIconTextureID(_ICON_DATABASE_EXPORT), ImVec2(18, 18)); 
            ImGui::SameLine();
            if (ImGui::MenuItem("Export Connection"))
            {
                setCurrentMenuItem(SelectedMenuItem::ExportConnection);
                std::cout << "Open the 'Export Connection' window" << std::endl;
            }
            ImGui::Image((void*)(intptr_t)getIconTextureID(_ICON_CREATE_DATABASE), ImVec2(18, 18)); 
            ImGui::SameLine();
            if (ImGui::MenuItem("Create Database"))
            {
                setCurrentMenuItem(SelectedMenuItem::CreateDatabase);
                std::cout << "Open the 'Create Database' window" << std::endl;
            }
            ImGui::Image((void*)(intptr_t)getIconTextureID(_ICON_DELETE_DATABASE), ImVec2(18, 18)); 
            ImGui::SameLine();
            if (ImGui::MenuItem("Delete Database"))
            {
                setCurrentMenuItem(SelectedMenuItem::DeleteDatabase);
                std::cout << "Open the 'Delete Database' window" << std::endl;
            }
            ImGui::Image((void*)(intptr_t)getIconTextureID(_ICON_DATABASE_BACKUP), ImVec2(18, 18)); 
            ImGui::SameLine();
            if (ImGui::MenuItem("Backup Database"))
            {
            setCurrentMenuItem(SelectedMenuItem::BackupDatabase);
                std::cout << "Open the 'Backup Database' window" << std::endl;
            }
            ImGui::Image((void*)(intptr_t)getIconTextureID(_ICON_RESTORE), ImVec2(18, 18)); 
            ImGui::SameLine();
            if (ImGui::MenuItem("Restore Database"))
            {
                setCurrentMenuItem(SelectedMenuItem::RestoreDatabase);
                std::cout << "Open the 'Restore Database' window" << std::endl;
            }
            ImGui::EndMenu();
        }
        ImGui::Image((void*)(intptr_t)getIconTextureID(_ICON_TOOLS), ImVec2(18, 18)); 
        ImGui::SameLine();
        if (ImGui::BeginMenu("Tools"))
        {
            ImGui::Image((void*)(intptr_t)getIconTextureID(_ICON_VISUALIZE_DATABASE), ImVec2(18, 18)); 
            ImGui::SameLine();
            if (ImGui::MenuItem("Visualize Database"))
            {
                setCurrentMenuItem(SelectedMenuItem::VisualizeDatabase);
                std::cout << "Open the 'Visualize Database' window" << std::endl;
            }
            ImGui::Image((void*)(intptr_t)getIconTextureID(_ICON_DATABASE_LOGS), ImVec2(18, 18)); 
            ImGui::SameLine();
            if (ImGui::MenuItem("Database Logs"))
            {
                setCurrentMenuItem(SelectedMenuItem::DatabaseLogs);
                std::cout << "Open the 'Database Logs' window" << std::endl;
            }
            ImGui::EndMenu();
        }
        ImGui::Image((void*)(intptr_t)getIconTextureID(_ICON_SETTINGS), ImVec2(18, 18)); 
        ImGui::SameLine();
        if (ImGui::BeginMenu("Settings"))
        {
            ImGui::Image((void*)(intptr_t)getIconTextureID(_ICON_PREFERENCES), ImVec2(18, 18)); 
            ImGui::SameLine();
            if (ImGui::MenuItem("Preferences"))
            {
                setCurrentMenuItem(SelectedMenuItem::Preferences);
                std::cout << "Open the 'Preferences' window" << std::endl;
            }
            ImGui::Image((void*)(intptr_t)getIconTextureID(_ICON_APPERANCE), ImVec2(18, 18)); 
            ImGui::SameLine();
            if (ImGui::MenuItem("Appearance"))
            {
                setCurrentMenuItem(SelectedMenuItem::Appearance);
                std::cout << "Open the 'Appearance' window" << std::endl;
            }
            ImGui::EndMenu();
        }
        ImGui::Image((void*)(intptr_t)getIconTextureID(_ICON_HELP), ImVec2(18, 18)); 
        ImGui::SameLine();
        if (ImGui::BeginMenu("Help"))
        {
            ImGui::Image((void*)(intptr_t)getIconTextureID(_ICON_DOCS), ImVec2(18, 18)); 
            ImGui::SameLine();
            if (ImGui::MenuItem("Docs"))
            {
                setCurrentMenuItem(SelectedMenuItem::Docs);
                std::cout << "Open the 'Docs' window" << std::endl;
            }
            ImGui::Image((void*)(intptr_t)getIconTextureID(_ICON_UPDATE), ImVec2(18, 18)); 
            ImGui::SameLine();
            if (ImGui::MenuItem("Check for Updates"))
            {
                setCurrentMenuItem(SelectedMenuItem::CheckForUpdates);
                std::cout << "Open the 'Check for Updates' window" << std::endl;
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

void T_data::setBackgroundTextureID(const GLuint backgroundTextureID)
{ 
    _backgroundTextureID = backgroundTextureID;
}

void T_data::setWindow(GLFWwindow* window)
{
    _window = window;
}

void T_data::setIo(ImGuiIO* io)
{
    _io = io;
}

void T_data::setCurrentMenuItem(SelectedMenuItem menuItem) 
{
    _currentMenuItem = menuItem;
}

GLuint T_data::getBackgroundTextureID() const 
{
    return _backgroundTextureID;
}

GLFWwindow* T_data::getWindow() 
{
    return _window;
}

ImGuiIO* T_data::getIo() 
{
    return _io;
}

SelectedMenuItem T_data::getCurrentMenuItem() const 
{
    return _currentMenuItem;
}

void T_data::addIconTextureID(const std::string& name, GLuint textureID)
{
    this->_iconTextureIDs[name] = textureID;
}

GLuint T_data::getIconTextureID(const std::string& name) const
{
    auto it = this->_iconTextureIDs.find(name);
    if (it != this->_iconTextureIDs.end()) {
        return it->second;
    }
    return (0);
}




// ########################### Cleanup function ###########################
void T_data::cleanup()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    if (_window) {
        glfwDestroyWindow(_window);
    }
    glfwTerminate();
}

// ########################### MainLoop ###########################
bool T_data::mainLoop()
{
    while (!glfwWindowShouldClose(getWindow()))
    {
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Fetch the new window size
        ImVec2 windowSize = ImGui::GetIO().DisplaySize;
        //set params to render
        renderSelected(windowSize);
        renderMenuBar();
        ImGui::End();
        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(getWindow(), &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(getWindow());
    }
    return EXIT_SUCCESS;
}

// ########################### Main app (Init & cleanup) ###########################
int T_data::initGui()
{
    //init window && io && textures
    if (initImgui())
        return (EXIT_FAILURE);

    // Setup ImGui binding
    if (!setupImGui())
    {
        std::cerr << "Failed to setup ImGui." << std::endl;
        glfwDestroyWindow(getWindow());
        glfwTerminate();
        return (EXIT_FAILURE);
    }
    if (mainLoop())
    {
        std::cerr << "An error occurred during the main loop." << std::endl;
        cleanup();
        return (EXIT_FAILURE);
    }
    // Cleanup
    cleanup();
    return (EXIT_SUCCESS);
}

void SetupStyles()
{
    // Style variables
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10, 10));
    ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 4.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 10)); // Increase spacing between elements
    ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, ImVec2(0, 10)); // Increase inner spacing for better readability
    
    // Color adjustments for a cohesive look
    const ImVec4 darkBg(0.1f, 0.1f, 0.1f, 1.0f);
    const ImVec4 lightText(1.0f, 1.0f, 1.0f, 1.0f);
    const ImVec4 accentColor(0.26f, 0.59f, 0.98f, 1.5f);
    const ImVec4 hoverColor = ImVec4(accentColor.x * 1.1f, accentColor.y * 1.1f, accentColor.z * 1.5f, 1.0f);
    const ImVec4 activeColor = ImVec4(accentColor.x * 0.9f, accentColor.y * 0.9f, accentColor.z * 0.9f, 1.0f);

    // Applying base colors
    ImGui::PushStyleColor(ImGuiCol_WindowBg, darkBg);
    ImGui::PushStyleColor(ImGuiCol_Text, lightText);
    ImGui::PushStyleColor(ImGuiCol_Button, accentColor);
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, hoverColor);
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, activeColor);
    ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.2f, 0.25f, 0.25f, 1.0f));
}

void RenderDatabaseTypeSelection(int& currentDbTypeIndex)
{
    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();
    static const char* dbTypes[] = {"PostgreSQL", "MySQL", "Sqlite"};
    ImGui::Text("Set Database Type, search will be based on this type of database");
    ImGui::Combo("##DatabaseType", &currentDbTypeIndex, dbTypes, IM_ARRAYSIZE(dbTypes));
}

void RenderIPRangeInput(bool& useLocalhost, char (&startIp)[16], char (&endIp)[16])
{
    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();
    ImGui::Checkbox("Scan localhost instead of IP range", &useLocalhost);
    if (!useLocalhost)
    {
        ImGui::Text("Start IP:");
        ImGui::SameLine();
        ImGui::InputText("##StartIP", startIp, IM_ARRAYSIZE(startIp), ImGuiInputTextFlags_CharsDecimal | ImGuiInputTextFlags_CharsNoBlank | ImGuiInputTextFlags_CallbackCharFilter, CharFilterIpAddress);
        
        ImGui::Text("  End IP:");
        ImGui::SameLine();
        ImGui::InputText("##EndIP", endIp, IM_ARRAYSIZE(endIp), ImGuiInputTextFlags_CharsDecimal | ImGuiInputTextFlags_CharsNoBlank | ImGuiInputTextFlags_CallbackCharFilter, CharFilterIpAddress);
    } else
    {
        strcpy(startIp, "127.0.0.1");
        strcpy(endIp, "127.0.0.1");
    }
}

void RenderPortRangeInput(char (&startPort)[6], char (&endPort)[6])
{
    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();
    ImGui::Text("Port range to scan for databases");
    ImGui::Text("Start port:");
    ImGui::SameLine();
    ImGui::InputText("##StartPort", startPort, IM_ARRAYSIZE(startPort), ImGuiInputTextFlags_CharsDecimal | ImGuiInputTextFlags_CharsNoBlank, CharFilterDatabasePort);
    ImGui::Text("  End port:");
    ImGui::SameLine();
    ImGui::InputText("##EndPort", endPort, IM_ARRAYSIZE(endPort), ImGuiInputTextFlags_CharsDecimal | ImGuiInputTextFlags_CharsNoBlank, CharFilterDatabasePort);
}

void RenderResetAndSearchButtons(int& currentDbTypeIndex, char* startPort, char* endPort, char* startIp, char* endIp, bool& useLocalhost)
{
    static const char* dbTypes[] = {"PostgreSQL", "MySQL", "Sqlite"};
    ImGui::Combo("##DatabaseTypeCombo", &currentDbTypeIndex, dbTypes, IM_ARRAYSIZE(dbTypes));
    // Buttons for actions
    if (ImGui::Button("Reset##ResetButton", ImVec2(120, 0)))
    {
        // Reset the search parameters
        currentDbTypeIndex = 0;
        startPort[0] = '\0';
        endPort[0] = '\0';
        startIp[0] = '\0';
        endIp[0] = '\0';
        useLocalhost = false;
    }
    ImGui::SameLine();
    bool validInputs = (useLocalhost && strlen(startPort) > 0 && strlen(endPort) > 0) || (isValidIpAddress(startIp) && isValidIpAddress(endIp) && strlen(startPort) > 0 && strlen(endPort) > 0);
    if (validInputs && ImGui::Button("Search##SearchButton", ImVec2(120, 0)))
    {
        DataBaseCrawler dbCrawler(startPort, endPort, startIp, endIp, dbTypes[currentDbTypeIndex]);
        std::vector<DatabaseInfo> databaseInfos = dbCrawler.detectDatabases();

        for (const auto& info : databaseInfos) {
            std::cout << "------------------------" << std::endl;
            std::cout << "StartTime: " << info.scanStartTime << std::endl;
            std::cout << "State: " << info.state << std::endl;
            std::cout << "databasetype: " << info.type << std::endl;
            std::cout << "databasehost: " << info.host << std::endl;
            std::cout << "databaseport: " << info.port << std::endl;
            std::cout << "databaseservice: " << info.service << std::endl;
            std::cout << "databaseversion: " << info.version << std::endl;
            std::cout << "------------------------" << std::endl;
        }
    }
}

// Main function refactored
void T_data::renderSearchOptions(ImVec2 windowSize)
{
    SetupStyles();
    ImGui::Begin("##DatabaseList", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
    // Add more space between style setup and GUI elements

    ImGui::SetWindowPos(ImVec2(0, 20), ImGuiCond_Always);
    ImGui::SetWindowSize(windowSize, ImGuiCond_Always);
    if (this->getCurrentMenuItem() == SelectedMenuItem::ListDatabases)
    {
        static int currentDbTypeIndex = 0;
        static bool useLocalhost = false;
        static char startIp[16] = "";
        static char endIp[16] = "";
        static char startPort[6] = "";
        static char endPort[6] = "";

        ImGui::TextColored(ImVec4(0.0f, 0.0f, 1.0f, 1.0f), "Database Search Options:"); // Use TextColored to highlight the topic with blue color



        // Dropdown menu for database type selection
        RenderDatabaseTypeSelection(currentDbTypeIndex);

        RenderIPRangeInput(useLocalhost, startIp, endIp);
        RenderPortRangeInput(startPort, endPort);
        bool validInputs = (useLocalhost && strlen(startPort) > 0 && strlen(endPort) > 0) || (isValidIpAddress(startIp) && isValidIpAddress(endIp) && strlen(startPort) > 0 && strlen(endPort) > 0);
        if (validInputs)
            RenderResetAndSearchButtons(currentDbTypeIndex, startPort, endPort, startIp, endIp, useLocalhost);
    }
    //TODO: Add Table to show the results of the search
    ImGui::PopStyleColor(6); // Pop style colors for text, buttons
    ImGui::PopStyleVar(5); // Pop style var
    
}