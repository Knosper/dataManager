#include "T_Data.hpp"
#include "DatabaseCrawler.hpp"
#include "utils.hpp"

void T_data::renderSelected(ImVec2 windowSize)
{
    switch (this->getCurrentMenuItem())
    {
        case AppConfig::SelectedMenuItem::StartPage:
        {
            this->renderBackground(windowSize);
            break;
        }
        case AppConfig::SelectedMenuItem::ListDatabases:
        {
            renderListDataBases(windowSize);
            break;
        }
        case AppConfig::SelectedMenuItem::NewConnection:
            break;
        case AppConfig::SelectedMenuItem::ManageConnections:
            break;
        case AppConfig::SelectedMenuItem::ImportConnection:
            break;
        case AppConfig::SelectedMenuItem::ExportConnection:
            break;
        case AppConfig::SelectedMenuItem::CreateDatabase:
            break;
        case AppConfig::SelectedMenuItem::DeleteDatabase:
            break;
        case AppConfig::SelectedMenuItem::BackupDatabase:
            break;
        case AppConfig::SelectedMenuItem::RestoreDatabase:
            break;
        case AppConfig::SelectedMenuItem::VisualizeDatabase:
            break;
        case AppConfig::SelectedMenuItem::DatabaseLogs:
            break;
        case AppConfig::SelectedMenuItem::Preferences:
            break;
        case AppConfig::SelectedMenuItem::Appearance:
            break;
        case AppConfig::SelectedMenuItem::Docs:
            break;
        case AppConfig::SelectedMenuItem::CheckForUpdates:
            break;
        default:
        {
            renderBackground(windowSize);
            break;
        }
    }
}

void T_data::renderMenuBar()
{
    if (ImGui::BeginMainMenuBar())
    {
        ImGui::Image(reinterpret_cast<void*>(static_cast<intptr_t>(getIconTextureID(AppConfig::_ICON_DATABASE))), ImVec2(18, 18));
        ImGui::SameLine();
        if (ImGui::BeginMenu("Database"))
        {
            ImGui::Image(reinterpret_cast<void*>(static_cast<intptr_t>(getIconTextureID(AppConfig::_ICON_LIST_DATABASE))), ImVec2(18, 18));
            ImGui::SameLine();
            if (ImGui::MenuItem("List Databases"))
            {
                setCurrentMenuItem(AppConfig::SelectedMenuItem::ListDatabases);
                std::cout << "List all detected databases" << std::endl;
            }
            ImGui::Image(reinterpret_cast<void*>(static_cast<intptr_t>(getIconTextureID(AppConfig::_ICON_NEW_CONNECTION))), ImVec2(18, 18));
            ImGui::SameLine();
            if (ImGui::MenuItem("New Connection"))
            {
                setCurrentMenuItem(AppConfig::SelectedMenuItem::NewConnection);
                std::cout << "Open the 'New Connection' Input window" << std::endl;
            }
            ImGui::Image(reinterpret_cast<void*>(static_cast<intptr_t>(getIconTextureID(AppConfig::_ICON_MANAGE_CONNECTION))), ImVec2(18, 18));
            ImGui::SameLine();
            if (ImGui::MenuItem("Manage Connections"))
            {
                setCurrentMenuItem(AppConfig::SelectedMenuItem::ManageConnections);
                std::cout << "Open the 'Manage Connections' window" << std::endl;
            }
            ImGui::Image(reinterpret_cast<void*>(static_cast<intptr_t>(getIconTextureID(AppConfig::_ICON_DATABASE_IMPORT))), ImVec2(18, 18));
            ImGui::SameLine();
            if (ImGui::MenuItem("Import Connection"))
            {
                setCurrentMenuItem(AppConfig::SelectedMenuItem::ImportConnection);
                std::cout << "Open the 'Import Connection' window" << std::endl;
            }
            ImGui::Image(reinterpret_cast<void*>(static_cast<intptr_t>(getIconTextureID(AppConfig::_ICON_DATABASE_EXPORT))), ImVec2(18, 18));
            ImGui::SameLine();
            if (ImGui::MenuItem("Export Connection"))
            {
                setCurrentMenuItem(AppConfig::SelectedMenuItem::ExportConnection);
                std::cout << "Open the 'Export Connection' window" << std::endl;
            }
            ImGui::Image(reinterpret_cast<void*>(static_cast<intptr_t>(getIconTextureID(AppConfig::_ICON_CREATE_DATABASE))), ImVec2(18, 18));
            ImGui::SameLine();
            if (ImGui::MenuItem("Create Database"))
            {
                setCurrentMenuItem(AppConfig::SelectedMenuItem::CreateDatabase);
                std::cout << "Open the 'Create Database' window" << std::endl;
            }
            ImGui::Image(reinterpret_cast<void*>(static_cast<intptr_t>(getIconTextureID(AppConfig::_ICON_DELETE_DATABASE))), ImVec2(18, 18));
            ImGui::SameLine();
            if (ImGui::MenuItem("Delete Database"))
            {
                setCurrentMenuItem(AppConfig::SelectedMenuItem::DeleteDatabase);
                std::cout << "Open the 'Delete Database' window" << std::endl;
            }
            ImGui::Image(reinterpret_cast<void*>(static_cast<intptr_t>(getIconTextureID(AppConfig::_ICON_DATABASE_BACKUP))), ImVec2(18, 18));
            ImGui::SameLine();
            if (ImGui::MenuItem("Backup Database"))
            {
                setCurrentMenuItem(AppConfig::SelectedMenuItem::BackupDatabase);
                std::cout << "Open the 'Backup Database' window" << std::endl;
            }
            ImGui::Image(reinterpret_cast<void*>(static_cast<intptr_t>(getIconTextureID(AppConfig::_ICON_RESTORE))), ImVec2(18, 18));
            ImGui::SameLine();
            if (ImGui::MenuItem("Restore Database"))
            {
                setCurrentMenuItem(AppConfig::SelectedMenuItem::RestoreDatabase);
                std::cout << "Open the 'Restore Database' window" << std::endl;
            }
            ImGui::EndMenu();
        }
        ImGui::Image(reinterpret_cast<void*>(static_cast<intptr_t>(getIconTextureID(AppConfig::_ICON_TOOLS))), ImVec2(18, 18));
        ImGui::SameLine();
        if (ImGui::BeginMenu("Tools"))
        {
            ImGui::Image(reinterpret_cast<void*>(static_cast<intptr_t>(getIconTextureID(AppConfig::_ICON_VISUALIZE_DATABASE))), ImVec2(18, 18));
            ImGui::SameLine();
            if (ImGui::MenuItem("Visualize Database"))
            {
                setCurrentMenuItem(AppConfig::SelectedMenuItem::VisualizeDatabase);
                std::cout << "Open the 'Visualize Database' window" << std::endl;
            }
            ImGui::Image(reinterpret_cast<void*>(static_cast<intptr_t>(getIconTextureID(AppConfig::_ICON_DATABASE_LOGS))), ImVec2(18, 18));
            ImGui::SameLine();
            if (ImGui::MenuItem("Database Logs"))
            {
                setCurrentMenuItem(AppConfig::SelectedMenuItem::DatabaseLogs);
                std::cout << "Open the 'Database Logs' window" << std::endl;
            }
            ImGui::EndMenu();
        }
        ImGui::Image(reinterpret_cast<void*>(static_cast<intptr_t>(getIconTextureID(AppConfig::_ICON_SETTINGS))), ImVec2(18, 18));
        ImGui::SameLine();
        if (ImGui::BeginMenu("Settings"))
        {
            ImGui::Image(reinterpret_cast<void*>(static_cast<intptr_t>(getIconTextureID(AppConfig::_ICON_PREFERENCES))), ImVec2(18, 18));
            ImGui::SameLine();
            if (ImGui::MenuItem("Preferences"))
            {
                setCurrentMenuItem(AppConfig::SelectedMenuItem::Preferences);
                std::cout << "Open the 'Preferences' window" << std::endl;
            }
            ImGui::Image(reinterpret_cast<void*>(static_cast<intptr_t>(getIconTextureID(AppConfig::_ICON_APPERANCE))), ImVec2(18, 18));
            ImGui::SameLine();
            if (ImGui::MenuItem("Appearance"))
            {
                setCurrentMenuItem(AppConfig::SelectedMenuItem::Appearance);
                std::cout << "Open the 'Appearance' window" << std::endl;
            }
            ImGui::EndMenu();
        }
        ImGui::Image(reinterpret_cast<void*>(static_cast<intptr_t>(getIconTextureID(AppConfig::_ICON_HELP))), ImVec2(18, 18));
        ImGui::SameLine();
        if (ImGui::BeginMenu("Help"))
        {
            ImGui::Image(reinterpret_cast<void*>(static_cast<intptr_t>(getIconTextureID(AppConfig::_ICON_DOCS))), ImVec2(18, 18));
            ImGui::SameLine();
            if (ImGui::MenuItem("Docs"))
            {
                setCurrentMenuItem(AppConfig::SelectedMenuItem::Docs);
                std::cout << "Open the 'Docs' window" << std::endl;
            }
            ImGui::Image(reinterpret_cast<void*>(static_cast<intptr_t>(getIconTextureID(AppConfig::_ICON_UPDATE))), ImVec2(18, 18));
            ImGui::SameLine();
            if (ImGui::MenuItem("Check for Updates"))
            {
                setCurrentMenuItem(AppConfig::SelectedMenuItem::CheckForUpdates);
                std::cout << "Open the 'Check for Updates' window" << std::endl;
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
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

void RenderResetAndSearchButtons(std::string currentDbType, char* startPort, char* endPort, char* startIp, char* endIp, bool& useLocalhost)
{
    // Buttons for actions
    if (ImGui::Button("Reset##ResetButton", ImVec2(200, 40)))
    {
        startPort[0] = '\0';
        endPort[0] = '\0';
        startIp[0] = '\0';
        endIp[0] = '\0';
        useLocalhost = false;
    }
    ImGui::SameLine();
    bool validInputs = (useLocalhost && strlen(startPort) > 0 && strlen(endPort) > 0) || (isValidIpAddress(startIp) && isValidIpAddress(endIp) && strlen(startPort) > 0 && strlen(endPort) > 0);
    if (validInputs && ImGui::Button("Search##SearchButton", ImVec2(200, 40)))
    {
        DatabaseCrawler dbCrawler(startPort, endPort, startIp, endIp, currentDbType);
        std::vector<DatabaseInfo> databaseInfos = dbCrawler.detectDatabases();

        for (const auto& _info : databaseInfos) {
            std::cout << "------------------------" << std::endl;
            std::cout << "StartTime: " << _info._scanStartTime << std::endl;
            std::cout << "State: " << _info._state << std::endl;
            std::cout << "databasetype: " << _info._type << std::endl;
            std::cout << "databasehost: " << _info._host << std::endl;
            std::cout << "databaseport: " << _info._port << std::endl;
            std::cout << "databaseservice: " << _info._service << std::endl;
            std::cout << "databaseversion: " << _info._version << std::endl;
            std::cout << "------------------------" << std::endl;
        }
        startPort[0] = '\0';
        endPort[0] = '\0';
        startIp[0] = '\0';
        endIp[0] = '\0';
        useLocalhost = false;
    }
}

// Main function for the first page "List Databases"
void T_data::renderListDataBases(ImVec2 windowSize)
{
    SetupStyles();
    ImGui::Begin("##DatabaseList", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);

    // Add more space between style setup and GUI elements
    ImGui::SetWindowPos(ImVec2(0, 20), ImGuiCond_Always);
    ImGui::SetWindowSize(windowSize, ImGuiCond_Always);
    if (this->getCurrentMenuItem() == AppConfig::SelectedMenuItem::ListDatabases)
    {
        static const char* dbTypes[] = {"PostgreSQL", "MySQL", "Sqlite"};
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
            RenderResetAndSearchButtons(dbTypes[currentDbTypeIndex], startPort, endPort, startIp, endIp, useLocalhost);
    }
    //TODO: Add Table to show the results of the search
    ImGui::PopStyleColor(6); // Pop style colors for text, buttons
    ImGui::PopStyleVar(5); // Pop style var
}
