//Data.hpp
#pragma once
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "constants.hpp"
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <thread>
#include <mutex>

class Data
{
public:
    int _cpuCores;

    //Constructor Destructor
    Data();
    ~Data();

    // High-Level Functional Methods
    int                 initImgui();
    bool                setupImGui();
    void                loadIcons();
    GLuint              loadImage(const char* imagePath);

    // UI Render Methods
    void                renderSelected(const ImVec2& windowSize);
    void                renderBackground(const ImVec2& windowSize);
    void                renderMenuBar();

    // Setter methods
    void                setBackgroundTextureID(const GLuint& backgroundTextureID);
    void                setWindow(GLFWwindow* window);
    void                setIo(ImGuiIO* io);
    void                setCurrentMenuItem(AppConfig::SelectedMenuItem menuItem);
    void                setDataBaseInfos(const std::vector<DatabaseInfo>& databaseInfos);

    // Getter methods
    GLuint                          getBackgroundTextureID() const;
    GLFWwindow*                     getWindow() const;
    ImGuiIO*                        getIo() const;
    AppConfig::SelectedMenuItem     getCurrentMenuItem() const;
    std::vector<DatabaseInfo>       getDataBaseInfos()  const;
    

    void    cleanup();
    bool    mainLoop();
    int     initGui();

    //Menu detectDatabases
    void                                    renderDetectDatabases(const ImVec2& windowSize);
    void                                    SetupStyles();
    std::vector<DatabaseInfo>               RenderResetAndSearchButtons(std::string currentDbType, char* startPort, char* endPort, char* startIp, char* endIp, bool& useLocalhost);
    void                                    RenderSearchResultTable();
    void                                    RenderPortRangeInput(char (&startPort)[6], char (&endPort)[6]);
    void                                    RenderIPRangeInput(bool& useLocalhost, char (&startIp)[16], char (&endIp)[16]);

private:
    GLuint                                  _backgroundTextureID;
    std::unordered_map<std::string, GLuint> _iconTextureIDs; 
    GLFWwindow*                             _window;      
    ImGuiIO*                                _io;            
    AppConfig::SelectedMenuItem             _currentMenuItem;
    std::vector<DatabaseInfo>               _databaseInfos;
    
    //private methods
    void                addIconTextureID(const std::string& name, const GLuint& textureID);
    GLuint              getIconTextureID(const std::string& name) const;
};