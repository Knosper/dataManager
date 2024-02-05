#pragma once
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define _THUB_PATH "misc/Thub.jpg"
#define _ICON_PATH "misc/Icon.jpg"
//#define _ICON_PATH "misc/Icon.jpg" TODO!


class T_data
{
private:
    /*bool        _dataBaseConnection;
    std::string _databaseType; // e.g., "MySQL", "SQLite", "PostgreSQL"
    std::string _databaseHost; // e.g., "localhost", "192.168.1.1"
    int         _databasePort; // e.g., 3306 for MySQL
    std::string _databaseName; // e.g., "myDatabase"
    std::string _username;     // e.g., "user123"
    std::string _password;     // e.g., "1"*/
    GLuint      _backgroundTextureID; //Path to image
    GLuint      _iconTextureID; //Path to Icon
    GLFWwindow* _window;        //App window

public:
    //status
    bool        _status;

    //Constructor Destructor
    T_data();
    ~T_data();

    // Setter methods
    void setBackgroundTextureID(const GLuint backgroundTextureID) { _backgroundTextureID = backgroundTextureID; }
    void setIconTextureID(const GLuint iconTextureID) { _iconTextureID = iconTextureID; }
    void setWindow(GLFWwindow* window) { _window = window; }

    // Getter methods
    GLuint getBackgroundTextureID() const { return _backgroundTextureID; }
    GLuint getIconTextureID() const { return _iconTextureID; }
    GLFWwindow* getWindow() { return _window; }


    /*void setDatabaseConnection(const bool& status) { _dataBaseConnection = status; }
    void setDatabaseType(const std::string& type) { _databaseType = type; }
    void setDatabaseHost(const std::string& host) { _databaseHost = host; }
    void setDatabasePort(int port) { _databasePort = port; }
    void setDatabaseName(const std::string& name) { _databaseName = name; }
    void setUsername(const std::string& username) { _username = username; }
    void setPassword(const std::string& password) { _password = password; }

    // Getter methods
    bool getDatabaseConnection() const { return _dataBaseConnection; }
    std::string getDatabaseType() const { return _databaseType; }
    std::string getDatabaseHost() const { return _databaseHost; }
    int getDatabasePort() const { return _databasePort; }
    std::string getDatabaseName() const { return _databaseName; }
    std::string getUsername() const { return _username; }
    std::string getPassword() const { return _password; }*/
};

