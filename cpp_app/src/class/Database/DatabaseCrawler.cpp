#include "DatabaseCrawler.hpp"

DataBaseCrawler::DataBaseCrawler()
{
    std::cout << "default DatabaseCrawler created" << std::endl;
}

DataBaseCrawler::DataBaseCrawler(std::string startPort, std::string endPort, std::string startIp, std::string endIp, std::string type): _startPort(startPort), _endPort(endPort), _startIp(startIp), _endIp(endIp), _type(type)
{
    std::cout << "default DatabaseCrawler created" << std::endl;
}

DataBaseCrawler::~DataBaseCrawler()
{
    std::cout << "default DatabaseCrawler destro" << std::endl;
}

std::vector<DatabaseInfo> DataBaseCrawler::detectDatabases()
{
    std::vector<DatabaseInfo> detectedDatabases;

    if (this->_type == "PostgreSQL") {
        detectedDatabases = detectPostgreSQLDatabases(); // Adjust this method to use startPort and endPort
    } else if (this->_type == "MySQL") {
        // detectedDatabases = detectMySQLDatabases();
    } else if (this->_type == "Sqlite") {
        // detectedDatabases = detectSqliteDatabases();
    }

    return detectedDatabases;
}

std::vector<DatabaseInfo> DataBaseCrawler::detectPostgreSQLDatabases() {
    std::vector<DatabaseInfo> postgresDatabases;
    std::time_t currentTime = std::time(nullptr);
    std::string startTime = std::asctime(std::localtime(&currentTime));
    startTime = startTime.substr(0, startTime.length() - 1); // Remove newline

    // Convert start and end ports to integers for the loop
    int startPortInt = std::stoi(this->_startPort);
    int endPortInt = std::stoi(this->_endPort);
    unsigned long startIpLong = ipToLong(this->_startIp);
    unsigned long endIpLong = ipToLong(this->_endIp);

    for (unsigned long ip = startIpLong; ip <= endIpLong; ++ip) {
        std::string currentIp = longToIp(ip);
        for (int port = startPortInt; port <= endPortInt; ++port) {
            std::string nmapCommand = "nmap -p " + std::to_string(port) + " --open -sV " + currentIp;
            std::cout << "Executing: " << nmapCommand << std::endl;

            FILE* pipe = popen(nmapCommand.c_str(), "r");
            if (!pipe) {
                std::cerr << "Failed to run nmap command" << std::endl;
                continue;
            }

            std::string nmapOutput;
            char buffer[128];
            while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
                nmapOutput += buffer;
            }
            pclose(pipe);

            // Parse the nmap output for each command executed
            std::regex servicePattern("(\\d+)/tcp\\s+(\\S+)\\s+[^\\s]+\\s+PostgreSQL\\s+(.*)");
            std::smatch serviceMatch;
            std::string::const_iterator searchStart(nmapOutput.cbegin());
            while (std::regex_search(searchStart, nmapOutput.cend(), serviceMatch, servicePattern)) {
                if (serviceMatch.size() > 3) {
                    DatabaseInfo dbInfo;
                    dbInfo.scanStartTime = startTime;
                    dbInfo.state = serviceMatch[2].str();
                    dbInfo.type = "nmap";
                    dbInfo.host = currentIp;
                    dbInfo.port = serviceMatch[1].str();
                    dbInfo.service = "PostgreSQL";
                    dbInfo.version = serviceMatch[3].str();
                    dbInfo.nmapOutput = nmapOutput;
                    postgresDatabases.push_back(dbInfo);
                }
                searchStart = serviceMatch.suffix().first;
            }
        }
    }

    if (postgresDatabases.empty()) {
        std::cout << "No PostgreSQL databases detected. Check nmap output." << std::endl;
    }
    return postgresDatabases;
}


std::vector<DatabaseInfo> DataBaseCrawler::detectMySQLDatabases()
{
    std::vector<DatabaseInfo> mysqlDatabases;
    std::time_t currentTime = std::time(nullptr); // Get the current system time
    std::string startTime = std::asctime(std::localtime(&currentTime)); // Convert the system time to a string

    // Remove the newline character at the end of the string
    startTime = startTime.substr(0, startTime.length() - 1);
    std::string nmapCommand = "nmap -p 3306 --open -sV 0.0.0.0";

    std::cout << "Starting nmap to detect MySQL databases..." << std::endl;
    
    // Open a pipe to execute the nmap command and read its output
    FILE* pipe = popen(nmapCommand.c_str(), "r");
    if (!pipe) {
        perror("popen");
        std::cout << "Error nmap..." << std::endl;
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
            dbInfo.scanStartTime = startTime;
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

std::vector<DatabaseInfo> DataBaseCrawler::detectSqliteDatabases()
{
    std::vector<DatabaseInfo> sqliteDatabases;
    std::time_t currentTime = std::time(nullptr); // Get the current system time
    std::string startTime = std::asctime(std::localtime(&currentTime)); // Convert the system time to a string

    // Remove the newline character at the end of the string
    startTime = startTime.substr(0, startTime.length() - 1);
    std::string nmapCommand = "nmap -p 5432 --open -sV 0.0.0.0";

    std::cout << "Starting nmap to detect MySQL databases..." << std::endl;
    
    // Open a pipe to execute the nmap command and read its output
    FILE* pipe = popen(nmapCommand.c_str(), "r");
    if (!pipe) {
        perror("popen");
        std::cout << "Error nmap..." << std::endl;
        return sqliteDatabases;
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
    std::regex pattern("^(\\d+)/tcp\\s+open\\s+mysql\\s+\\s+([^\\s]+)");
    std::smatch match;
    std::string::const_iterator searchStart(nmapOutput.cbegin());
    
    while (std::regex_search(searchStart, nmapOutput.cend(), match, pattern)) {
        if (match.size() == 3) {
            DatabaseInfo dbInfo;
            dbInfo.scanStartTime = startTime;
            dbInfo.host = "0.0.0.0";
            dbInfo.port = match[1].str();
            dbInfo.service = "sqlite";
            dbInfo.version = match[2].str();
            sqliteDatabases.push_back(dbInfo);
        }
        searchStart = match.suffix().first;
    }
    
    return sqliteDatabases;
}

std::ostream& operator<<(std::ostream& os, const DataBaseCrawler& crawler)
{
    if (crawler.detectedDatabases.empty())
    {
        os << "No databases detected." << std::endl;
        return os;
    }
    os << "Detected Databases:" << std::endl;
    for (const auto& database : crawler.detectedDatabases)
    {
        os << "Host: " << database.host << ", Type: " << database.type << std::endl;
    }
    return os;
}
