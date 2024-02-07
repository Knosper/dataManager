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
    //Scan Results
    std::string _scanStartTime; // Time the scan was started
    std::string _port;    // Port number the service is running on
    std::string _ip;    // IP address or hostname of the scanned server
    std::string _state;   // State of the scanned server
    std::string _service; // Service name, e.g., "postgresql"
    std::string _version; // Version of the detected service
    std::string _nmapOutput; // Full nmap output (not applicable for file-based databases)

    //Scan Parameters
    std::string _type;    // Type of scan or protocol used for the scan
    std::string _host;    // IP address or hostname of the scanned server
    std::string _dbName;  // Database name (not applicable for nmap output)
    std::string _Startport; // Start port for the scan
    std::string _endPort; // End port for the scan
    std::string _startIp; // Start IP for the scan
    std::string _endIp; // End IP for the scan
};

class DataBaseCrawler {
protected:
    DataBaseCrawler();
public:
    DataBaseCrawler(std::string startPort, std::string endPort, std::string startIp, std::string endIp, std::string type);
    ~DataBaseCrawler();

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
