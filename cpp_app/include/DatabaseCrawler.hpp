#include <vector>
#include <string>
#include <iostream>

struct DatabaseInfo {
    std::string type;       // e.g., "MySQL", "SQLite"
    std::string host;       // For network databases
    std::string dbName;     // Name of the database
    std::string filePath;   // For file-based databases like SQLite
    // ... other relevant information ...
};

class DatabaseCrawler {
public:
    DatabaseCrawler();
    ~DatabaseCrawler();

    // Function to detect databases. Returns a list of detected database info.
    std::vector<DatabaseInfo> detectDatabases();

private:
    // You might have private member functions or variables here
    // For example, functions to detect specific types of databases
    std::vector<DatabaseInfo> detectMySQLDatabases();
    std::vector<DatabaseInfo> detectSqliteDatabases();
    // ... other private methods or member variables ...
};
