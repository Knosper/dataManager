//DatabaseCrawler.hpp
#pragma once
#include "Data.hpp"
#include "Database.hpp"
#include "utils.hpp"
#include <constants.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <regex>
#include <ctime>
#include <csignal>

typedef struct s_searchOptions
{
    int startPort;
    int endPort;
    unsigned long startIp;
    unsigned long endIp;
    std::string currentIp;
    std::string startTime;
} t_searchOptions;

class DatabaseCrawler
{
protected:
    DatabaseCrawler();
public:
    DatabaseCrawler(const std::string& startPort, const std::string& endPort, const std::string& startIp, const std::string& endIp, std::string& type);
    ~DatabaseCrawler();

    // Function to detect databases. Returns a list of detected database info.
    std::vector<DatabaseInfo>   detectDatabases(const Data& data);

private:
    // Functions to detect specific types of databases
    std::vector<DatabaseInfo> detectMySQLDatabases();
    std::vector<DatabaseInfo> detectSqliteDatabases();
    std::vector<DatabaseInfo> detectPostgreSQLDatabases(const Data& data);
    std::vector<DatabaseInfo> detectedDatabases;

    std::string _startPort; // Start port for the scan
    std::string _endPort;   // End port for the scan
    std::string _startIp; // Start IP for the scan
    std::string _endIp;  // End IP for the scan
    std::string _type; // Type of database to scan for
};
