#include "DatabaseCrawler.hpp"

DatabaseCrawler::DatabaseCrawler() {
    // Constructor implementation
    std::cout << "default DatabaseCrawler created" << std::endl;
}

DatabaseCrawler::~DatabaseCrawler() {
    // Destructor implementation
    std::cout << "default DatabaseCrawler destro" << std::endl;
}

std::vector<DatabaseInfo> DatabaseCrawler::detectDatabases()
{
    std::vector<DatabaseInfo> detectedDatabases;

    // Call private functions to detect specific types of databases
    std::vector<DatabaseInfo> mysqlDatabases = detectMySQLDatabases();
    std::vector<DatabaseInfo> sqliteDatabases = detectSqliteDatabases();

    // Merge the detected databases into the final list
    detectedDatabases.insert(detectedDatabases.end(), mysqlDatabases.begin(), mysqlDatabases.end());
    detectedDatabases.insert(detectedDatabases.end(), sqliteDatabases.begin(), sqliteDatabases.end());

    return detectedDatabases;
}

std::vector<DatabaseInfo> DatabaseCrawler::detectMySQLDatabases()
{
    std::vector<DatabaseInfo> mysqlDatabases;
    std::string nmapCommand = "nmap -p 5432 --open -sV 0.0.0.0";
    
    // Open a pipe to execute the nmap command and read its output
    FILE* pipe = popen(nmapCommand.c_str(), "r");
    if (!pipe) {
        perror("popen");
        return mysqlDatabases;
    }
    
    char buffer[128];
    std::string nmapOutput = "";
    
    // Read the output of nmap into a string
    while (!feof(pipe)) {
        if (fgets(buffer, 128, pipe) != nullptr) {
            nmapOutput += buffer;
        }
    }
    
    // Close the pipe
    pclose(pipe);
    
    // Use regular expressions to parse the nmap output
    std::regex pattern("^(\\d+)/tcp\\s+open\\s+mysql\\s+MySQL\\s+([^\\s]+)");
    std::smatch match;
    std::string::const_iterator searchStart(nmapOutput.cbegin());
    
    while (std::regex_search(searchStart, nmapOutput.cend(), match, pattern)) {
        if (match.size() == 3) {
            DatabaseInfo dbInfo;
            dbInfo.host = "0.0.0.0";
            dbInfo.port = match[1].str();
            dbInfo.service = "MySQL";
            dbInfo.version = match[2].str();
            mysqlDatabases.push_back(dbInfo);
        }
        searchStart = match.suffix().first;
    }
    
    return mysqlDatabases;
}

std::vector<DatabaseInfo> DatabaseCrawler::detectSqliteDatabases()
{
    std::vector<DatabaseInfo> sqliteDatabases;

    // Implementation to detect SQLite databases
    return sqliteDatabases;
}