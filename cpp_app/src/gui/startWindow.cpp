#include "Macros.hpp"
#include "imgui.h"

void showDatabaseConfigWindow(Macros& params)
{
    static char dbHost[255] = "";
    static char dbName[255] = "";
    static char dbUser[255] = "";
    static char dbPass[255] = "";
    static int dbPort = 0;

    ImGui::Begin("Database Configuration");

    ImGui::InputText("Host", dbHost, IM_ARRAYSIZE(dbHost));
    ImGui::InputText("Database Name", dbName, IM_ARRAYSIZE(dbName));
    ImGui::InputText("User", dbUser, IM_ARRAYSIZE(dbUser));
    ImGui::InputText("Password", dbPass, IM_ARRAYSIZE(dbPass));
    ImGui::InputInt("Port", &dbPort);

    if (ImGui::Button("Connect")) {
        params.setDatabaseHost(dbHost);
        params.setDatabaseName(dbName);
        params.setUsername(dbUser);
        params.setPassword(dbPass);
        params.setDatabasePort(dbPort);

        if (params.connectToDatabase()) {
            std::cout << "Connection established!" << std::endl;
        } else {
            std::cout << "Failed to connect to the database." << std::endl;
        }
    }

    ImGui::End();
}