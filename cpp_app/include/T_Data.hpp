#pragma once
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "constants.h"
#include <unordered_map>
#include <vector>
#include <algorithm>

class T_data
{
public:
    //Constructor Destructor
    T_data();
    ~T_data();

    // High-Level Functional Methods
    int                 initImgui();
    bool                setupImGui();
    void                loadIcons();
    GLuint              loadImage(const char* imagePath);

    // UI Render Methods
    void                renderSelected(ImVec2 windowSize);
    void                renderListDataBases(ImVec2 windowSize);
    void                renderBackground(ImVec2 windowSize);
    void                renderMenuBar();
    void                renderDatabaseSearch();

    // Setter methods
    void                setBackgroundTextureID(const GLuint backgroundTextureID);
    void                setWindow(GLFWwindow* window);
    void                setIo(ImGuiIO* io);
    void                setCurrentMenuItem(AppConfig::SelectedMenuItem menuItem);

    // Getter methods
    GLuint                          getBackgroundTextureID() const;
    GLFWwindow*                     getWindow();
    ImGuiIO*                        getIo();
    AppConfig::SelectedMenuItem    getCurrentMenuItem() const;


    void cleanup();
    bool mainLoop();
    int initGui();

private:
    GLuint                                  _backgroundTextureID;
    std::unordered_map<std::string, GLuint> _iconTextureIDs; 
    GLFWwindow*                             _window;      
    ImGuiIO*                                _io;            
    AppConfig::SelectedMenuItem             _currentMenuItem;
    
    void                addIconTextureID(const std::string& name, GLuint textureID);
    GLuint              getIconTextureID(const std::string& name) const;
};