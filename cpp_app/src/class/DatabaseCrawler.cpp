#include "DatabaseCrawler.hpp"

DatabaseCrawler::DatabaseCrawler() {
    // Constructor implementation
    std::cout << "default DatabaseCrawler created" << std::endl;
}

DatabaseCrawler::~DatabaseCrawler() {
    // Destructor implementation
    std::cout << "default DatabaseCrawler deleted" << std::endl;
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

    // Implementation to detect MySQL databases
    return mysqlDatabases;
}

std::vector<DatabaseInfo> DatabaseCrawler::detectSqliteDatabases()
{
    std::vector<DatabaseInfo> sqliteDatabases;

    // Implementation to detect SQLite databases
    return sqliteDatabases;
}