#pragma once
#include "Database.hpp"
#include "utils.hpp"
#include <constants.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <regex>
#include <ctime> // Include the <ctime> header

class DatabaseCrawler
{
protected:
    DatabaseCrawler();
public:
    DatabaseCrawler(const std::string& startPort, const std::string& endPort, const std::string& startIp, const std::string& endIp, std::string& type);
    ~DatabaseCrawler();

    // Function to detect databases. Returns a list of detected database info.
    std::vector<DatabaseInfo> detectDatabases();

private:
    // Functions to detect specific types of databases
    std::vector<DatabaseInfo> detectMySQLDatabases();
    std::vector<DatabaseInfo> detectSqliteDatabases();
    std::vector<DatabaseInfo> detectPostgreSQLDatabases();
    std::vector<DatabaseInfo> detectedDatabases;


    std::string _startPort; // Start port for the scan
    std::string _endPort;   // End port for the scan
    std::string _startIp; // Start IP for the scan
    std::string _endIp;  // End IP for the scan
    std::string _type; // Type of database to scan for

};
