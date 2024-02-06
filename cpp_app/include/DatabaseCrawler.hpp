#pragma once
#include "Database.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <regex>

struct DatabaseInfo {
    std::string type;       // e.g., "MySQL", "SQLite"
    std::string host;       // For network databases
    std::string dbName;     // Name of the database
    std::string filePath;   // For file-based databases like SQLite
    std::string port;
    std::string service;
    std::string version;
    // ... other relevant information ...
};

//TODO: Write cpp file for this class
class DataBaseCrawler {
public:
    DataBaseCrawler();
    ~DataBaseCrawler();

    // Function to detect databases. Returns a list of detected database info.
    std::vector<DatabaseInfo> detectDatabases();

private:
    // Functions to detect specific types of databases
    std::vector<DatabaseInfo> detectMySQLDatabases();
    std::vector<DatabaseInfo> detectSqliteDatabases();
    // ... other private methods or member variables ...
};
