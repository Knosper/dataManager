#include "Data.hpp"
#include "DatabaseCrawler.hpp"

void Data::SetupStyles()
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

static void RenderDatabaseTypeSelection(int& currentDbTypeIndex)
{
    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();
    static const char* dbTypes[] = {"PostgreSQL", "MySQL", "Sqlite"};
    ImGui::Text("Set Database Type, search will be based on this type of database");
    ImGui::Combo("##DatabaseType", &currentDbTypeIndex, dbTypes, IM_ARRAYSIZE(dbTypes));
}

void Data::RenderIPRangeInput(bool& useLocalhost, char (&startIp)[16], char (&endIp)[16])
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

void Data::RenderPortRangeInput(char (&startPort)[6], char (&endPort)[6])
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

void Data::RenderResetAndSearchButtons(std::string currentDbType, char* startPort, char* endPort, char* startIp, char* endIp, bool& useLocalhost)
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
void Data::renderDetectDatabases(const ImVec2& windowSize)
{
    SetupStyles();
    ImGui::Begin("##DatabaseList", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);

    // Add more space between style setup and GUI elements
    ImGui::SetWindowPos(ImVec2(0, 20), ImGuiCond_Always);
    ImGui::SetWindowSize(windowSize, ImGuiCond_Always);
    if (this->getCurrentMenuItem() == AppConfig::SelectedMenuItem::DetectDatabases)
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
