#pragma once
#include "Database.hpp"
#include "utils.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <regex>
#include <ctime> // Include the <ctime> header

struct DatabaseInfo
{
    std::string scanStartTime; // Time the scan was started
    std::string state;   // State of the scanned server
    std::string service; // Service name, e.g., "postgresql"
    std::string version; // Version of the detected service
    std::string nmapOutput; // Full nmap output (not applicable for file-based databases)

    std::string type;    // Type of scan or protocol used for the scan
    std::string host;    // IP address or hostname of the scanned server
    std::string dbName;  // Database name (not applicable for nmap output)
    std::string port;    // Port number the service is running on
};

class DataBaseCrawler {
protected:
    DataBaseCrawler();
public:
    DataBaseCrawler(std::string startPort, std::string endPort, std::string startIp, std::string endIp, std::string type);
    ~DataBaseCrawler();

    // Function to detect databases. Returns a list of detected database info.
    std::vector<DatabaseInfo> detectDatabases();

    // Overload the << operator to print the vector of DatabaseInfo objects
    friend std::ostream& operator<<(std::ostream& os, const DataBaseCrawler& crawler);

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

std::ostream& operator<<(std::ostream& os, const DataBaseCrawler& crawler);
