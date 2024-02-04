#pragma once
#include <iostream>

#define _THUB_PATH "misc/Thub.jpg"

class Macros
{
private:
    bool        _dataBaseConnection;
    std::string _databaseType; // e.g., "MySQL", "SQLite", "PostgreSQL"
    std::string _databaseHost; // e.g., "localhost", "192.168.1.1"
    int         _databasePort; // e.g., 3306 for MySQL
    std::string _databaseName; // e.g., "myDatabase"
    std::string _username;     // e.g., "user123"
    std::string _password;     // e.g., "1"

public:
    //status
    bool        _status;

    //Constructor Destructor
    Macros();
    ~Macros();

    // Setter methods
    void setDatabaseConnection(const bool& status) { _dataBaseConnection = status; }
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
    std::string getPassword() const { return _password; }

    // Function to establish a database connection
    bool connectToDatabase();
};

