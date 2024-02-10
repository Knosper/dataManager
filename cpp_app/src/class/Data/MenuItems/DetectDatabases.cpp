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
    ImGui::Text("Set Database Type:");
    ImGui::SetNextItemWidth(100);
    ImGui::Combo("##DatabaseType", &currentDbTypeIndex, dbTypes, IM_ARRAYSIZE(dbTypes));
}

void Data::RenderIPRangeInput(bool& useLocalhost, char (&startIp)[16], char (&endIp)[16])
{
    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();
    ImGui::Checkbox("Scan localhost instead of IP range", &useLocalhost);

    static bool startIpValid = true;
    static bool endIpValid = true;    

    if (!useLocalhost)
    {
        ImGui::Text("Start IP:");
        ImGui::SameLine();
        ImGui::SetNextItemWidth(100);
        if (ImGui::InputText("##StartIP", startIp, IM_ARRAYSIZE(startIp), ImGuiInputTextFlags_CharsDecimal | ImGuiInputTextFlags_CharsNoBlank | ImGuiInputTextFlags_CallbackCharFilter, CharFilterIpAddress))
        {
            // Validate the IP address whenever the input changes
            startIpValid = isValidIpAddress(startIp);
        }
        if (!startIpValid)
        {
            ImGui::TextColored(ImVec4(1,0,0,1), "Invalid IP address");
        }
        ImGui::Text("  End IP:");
        ImGui::SameLine();
        ImGui::SetNextItemWidth(100);
        if (ImGui::InputText("##EndIP", endIp, IM_ARRAYSIZE(endIp), ImGuiInputTextFlags_CharsDecimal | ImGuiInputTextFlags_CharsNoBlank | ImGuiInputTextFlags_CallbackCharFilter, CharFilterIpAddress))
        {
            endIpValid = isValidIpAddress(endIp);
        }
        if (!endIpValid)
        {
            ImGui::TextColored(ImVec4(1,0,0,1), "Invalid IP address");
        }
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
    ImGui::SetNextItemWidth(100);
    ImGui::InputText("##StartPort", startPort, IM_ARRAYSIZE(startPort), ImGuiInputTextFlags_CharsDecimal | ImGuiInputTextFlags_CharsNoBlank | ImGuiInputTextFlags_CallbackCharFilter, CharFilterDatabasePort);
    ImGui::Text("  End port:");
    ImGui::SameLine();
    ImGui::SetNextItemWidth(100);
    ImGui::InputText("##EndPort", endPort, IM_ARRAYSIZE(endPort), ImGuiInputTextFlags_CharsDecimal | ImGuiInputTextFlags_CharsNoBlank | ImGuiInputTextFlags_CallbackCharFilter, CharFilterDatabasePort);
}

std::vector<DatabaseInfo> Data::RenderResetAndSearchButtons(std::string currentDbType, char* startPort, char* endPort, char* startIp, char* endIp, bool& useLocalhost)
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
        std::vector<DatabaseInfo> databaseInfos = dbCrawler.detectDatabases(*this);
        for (const auto& _info : databaseInfos) {
            std::cout << "------------------------" << std::endl;
            std::cout << "Database Info: " << std::endl;
            std::cout << "------------------------" << std::endl;
            std::cout << "search options:" << std::endl;
            std::cout << "Type: " << _info._type << std::endl;
            std::cout << "Host: " << _info._host << std::endl;
            std::cout << "dbName: " << _info._dbName << std::endl;
            std::cout << "------------------------" << std::endl;
            std::cout << "------------------------" << std::endl;
            std::cout << "StartTime: " << _info._scanStartTime << std::endl;
            std::cout << "databaseport: " << _info._port << std::endl;
            std::cout << "databaseip: " << _info._ip << std::endl;
            std::cout << "State: " << _info._state << std::endl;
            std::cout << "databaseservice: " << _info._service << std::endl;
            std::cout << "databaseversion: " << _info._version << std::endl;
            std::cout << "nmapoutput: " << _info._nmapOutput << std::endl;
            std::cout << "------------------------" << std::endl;
        }
        startPort[0] = '\0';
        endPort[0] = '\0';
        startIp[0] = '\0';
        endIp[0] = '\0';
        useLocalhost = false;
        return (databaseInfos);
    }
    return (std::vector<DatabaseInfo>());
}

// Implement this based on your data structure
void SortData(std::vector<DatabaseInfo>& items, const ImGuiTableSortSpecs* sortSpecs)
{
    std::cout << "Todo: Implement sorting" << std::endl;
}

void Data::RenderSearchResultTable()
{
    ImGuiTableFlags flags = ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable
                            | ImGuiTableFlags_RowBg | ImGuiTableFlags_Borders | ImGuiTableFlags_NoBordersInBody
                            | ImGuiTableFlags_ScrollY | ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_Sortable;

    // Begin the table with a specified number of columns
    if (ImGui::BeginTable("##SearchResultTable", 8, flags))
    {
        ImGui::TableSetupScrollFreeze(0, 1); 
        ImGui::TableSetupColumn("#", ImGuiTableColumnFlags_WidthStretch | ImGuiTableColumnFlags_DefaultSort);
        ImGui::TableSetupColumn("DB Name", ImGuiTableColumnFlags_WidthStretch | ImGuiTableColumnFlags_DefaultSort);
        ImGui::TableSetupColumn("Scan Start Time", ImGuiTableColumnFlags_WidthStretch | ImGuiTableColumnFlags_DefaultSort);
        ImGui::TableSetupColumn("Port", ImGuiTableColumnFlags_WidthStretch | ImGuiTableColumnFlags_DefaultSort);
        ImGui::TableSetupColumn("IP", ImGuiTableColumnFlags_WidthStretch | ImGuiTableColumnFlags_DefaultSort);
        ImGui::TableSetupColumn("State", ImGuiTableColumnFlags_WidthStretch | ImGuiTableColumnFlags_DefaultSort);
        ImGui::TableSetupColumn("Service", ImGuiTableColumnFlags_WidthStretch | ImGuiTableColumnFlags_DefaultSort);
        ImGui::TableSetupColumn("Version", ImGuiTableColumnFlags_WidthStretch | ImGuiTableColumnFlags_DefaultSort);
        ImGui::TableHeadersRow();
        const ImGuiTableSortSpecs* sortSpecs = ImGui::TableGetSortSpecs();
        if (sortSpecs && sortSpecs->SpecsDirty)
        {
            SortData(_databaseInfos, sortSpecs);
            ImGui::TableGetSortSpecs()->SpecsDirty = false;
        }
        for (int row = 0; row < static_cast<int>(_databaseInfos.size()); row++)
        {
            ImGui::TableNextRow();
            for (int column = 0; column < 8; column++)
            {
                ImGui::TableSetColumnIndex(column);
                const auto& dbInfo = _databaseInfos[row];
                switch (column)
                {
                    case 0: ImGui::Text("%d", row + 1); break;
                    case 1: ImGui::Text("%s", dbInfo._dbName.c_str()); break;
                    case 2: ImGui::Text("%s", dbInfo._scanStartTime.c_str()); break;
                    case 3: ImGui::Text("%s", dbInfo._port.c_str()); break;
                    case 4: ImGui::Text("%s", dbInfo._ip.c_str()); break;
                    case 5: ImGui::Text("%s", dbInfo._state.c_str()); break;
                    case 6: ImGui::Text("%s", dbInfo._service.c_str()); break;
                    case 7: ImGui::Text("%s", dbInfo._version.c_str()); break;
                }
            }
        }
        ImGui::EndTable();
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
    static const char* dbTypes[] = {"PostgreSQL", "MySQL", "Sqlite"};
    static int currentDbTypeIndex = 0;
    static bool useLocalhost = false;
    static char startIp[16] = "";
    static char endIp[16] = "";
    static char startPort[6] = "";
    static char endPort[6] = "";
    ImGui::SetWindowFontScale(1.5f); 
    ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "Database Search Options:"); // Use TextColored to highlight the topic with blue color
    ImGui::SetWindowFontScale(1.0f);
    // Dropdown menu for database type selection
    RenderDatabaseTypeSelection(currentDbTypeIndex);
    RenderIPRangeInput(useLocalhost, startIp, endIp);
    RenderPortRangeInput(startPort, endPort);
    bool validInputs = (useLocalhost && strlen(startPort) > 0 && strlen(endPort) > 0) || (isValidIpAddress(startIp) && isValidIpAddress(endIp) && strlen(startPort) > 0 && strlen(endPort) > 0);
    if (validInputs)
        this->setDataBaseInfos(RenderResetAndSearchButtons(dbTypes[currentDbTypeIndex], startPort, endPort, startIp, endIp, useLocalhost));
    RenderSearchResultTable();
    //TODO: Add Table to show the results of the search
    ImGui::PopStyleColor(6); // Pop style colors for text, buttons
    ImGui::PopStyleVar(5); // Pop style var
}
