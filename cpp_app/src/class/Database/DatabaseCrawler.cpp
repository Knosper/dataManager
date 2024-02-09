#include "DatabaseCrawler.hpp"

DatabaseCrawler::DatabaseCrawler()
{
    std::cout << "default DatabaseCrawler created" << std::endl;
}

DatabaseCrawler::DatabaseCrawler(const std::string& startPort, const std::string& endPort, const std::string& startIp, const std::string& endIp, std::string& type): _startPort(startPort), _endPort(endPort), _startIp(startIp), _endIp(endIp), _type(type)
{
    std::cout << "default DatabaseCrawler created" << std::endl;
}

DatabaseCrawler::~DatabaseCrawler()
{
    std::cout << "default DatabaseCrawler destro" << std::endl;
}

std::vector<DatabaseInfo> DatabaseCrawler::detectDatabases(const Data& data)
{
    std::vector<DatabaseInfo> detectedDatabases;

    if (this->_type == "PostgreSQL") {
        detectedDatabases = detectPostgreSQLDatabases(data); // Adjust this method to use startPort and endPort
    } else if (this->_type == "MySQL") {
        // detectedDatabases = detectMySQLDatabases();
    } else if (this->_type == "Sqlite") {
        // detectedDatabases = detectSqliteDatabases();
    }

    return detectedDatabases;
}

static void parseNmapOutput(const std::string& nmapOutput, std::vector<DatabaseInfo>& databases, t_searchOptions searchOptions, std::mutex& database_vector_mutex)
{
    std::regex servicePattern("(\\d+)/tcp\\s+(\\S+)\\s+[^\\s]+\\s+PostgreSQL\\s+(.*)");
    std::smatch serviceMatch;
    std::string::const_iterator searchStart(nmapOutput.cbegin());
    static int index = 1;
    while (std::regex_search(searchStart, nmapOutput.cend(), serviceMatch, servicePattern))
    {
        if (serviceMatch.size() > 3)
        {
            DatabaseInfo dbInfo;
            dbInfo._type = "nmap";
            dbInfo._host = searchOptions.currentIp;
            dbInfo._dbName = "Postgres_" + std::to_string(index++) + "_db";
            dbInfo._scanStartTime = searchOptions.startTime;
            dbInfo._port = serviceMatch[1].str();
            dbInfo._ip = searchOptions.currentIp;
            dbInfo._state = serviceMatch[2].str();
            dbInfo._service = "PostgreSQL";
            dbInfo._version = serviceMatch[3].str();
            dbInfo._nmapOutput = nmapOutput;
            std::lock_guard<std::mutex> guard(database_vector_mutex);
            databases.push_back(dbInfo);
        }
        searchStart = serviceMatch.suffix().first;
    }
}

static int scanPortRangeForPostgres(int startPort, int endPort, t_searchOptions searchOptions, std::vector<DatabaseInfo>& postgresDatabases, std::mutex& database_vector_mutex)
{
    for (unsigned long ipLong = searchOptions.startIp; ipLong <= searchOptions.endIp; ipLong++)
    {
        searchOptions.currentIp = longToIp(ipLong);
        for (int port = startPort; port <= endPort; ++port)
        {
            std::string nmapCommand = "nmap -p " + std::to_string(port) + " --open -sV " + searchOptions.currentIp;
            std::cout << "Executing: " << nmapCommand << std::endl;
            try
            {
                FILE* pipe = popen(nmapCommand.c_str(), "r");
                if (!pipe) {
                    std::cerr << "Failed to run nmap command" << std::endl;
                    continue;
                }
                std::string nmapOutput;
                char buffer[128];
                while (!feof(pipe)) {
                    if (fgets(buffer, 128, pipe) != nullptr) {
                        nmapOutput += buffer;
                    }
                }
                pclose(pipe);
                parseNmapOutput(nmapOutput, postgresDatabases, searchOptions, database_vector_mutex);
            }
            catch (std::exception& e)
            {
                std::cerr << "Error running nmap command: " << e.what() << std::endl;
                return (EXIT_FAILURE);
            }
        }
    }
    return (EXIT_SUCCESS);
}

std::vector<DatabaseInfo> DatabaseCrawler::detectPostgreSQLDatabases(const Data& data)
{
    std::vector<DatabaseInfo> postgresDatabases; // Vector to store the detected databases
    t_searchOptions searchOptions; // Struct to store the search options

    // Get the current system time and convert it to a string
    std::time_t currentTime = std::time(nullptr);
    searchOptions.startTime = std::asctime(std::localtime(&currentTime));
    searchOptions.startTime = searchOptions.startTime.substr(0, searchOptions.startTime.length() - 1);

    // Convert start and end ports to integers for the loop
    searchOptions.startPort = std::stoi(this->_startPort);
    searchOptions.endPort = std::stoi(this->_endPort);
    searchOptions.startIp = ipToLong(this->_startIp);
    searchOptions.endIp = ipToLong(this->_endIp);

    std::vector<std::thread> threads;
    std::mutex database_vector_mutex;

    int totalPorts = searchOptions.endPort - searchOptions.startPort + 1;
    std::cout << "Total ports: " << totalPorts << std::endl;
    int portsPerThread = totalPorts / data._cpuCores;
    std::cout << "Ports per thread: " << portsPerThread << std::endl;
    int remainingPorts = totalPorts % data._cpuCores;
    std::cout << "Remaining ports: " << remainingPorts << std::endl;
   if (totalPorts <= data._cpuCores || data._cpuCores == 1)
   {
        std::thread worker([&]()
        {
            scanPortRangeForPostgres(searchOptions.startPort, searchOptions.endPort, searchOptions, postgresDatabases, database_vector_mutex);
        });
        worker.join();
    }
    else
    {
        int numThreads = std::min(totalPorts, data._cpuCores);
        int extraPorts = totalPorts % numThreads;
        // Calculate initial ports per thread and distribute any remaining ports
        int initialPortsPerThread = totalPorts / numThreads;
        for (int i = 0; i < numThreads; ++i)
        {
            int threadStartPort = searchOptions.startPort + i * initialPortsPerThread + std::min(i, extraPorts);
            int threadEndPort = threadStartPort + initialPortsPerThread - 1 + (i < extraPorts ? 1 : 0);
            threads.emplace_back(scanPortRangeForPostgres, threadStartPort, threadEndPort, searchOptions, std::ref(postgresDatabases), std::ref(database_vector_mutex));
        }
    }
    // Join threads
    for (auto& thread : threads) {
        thread.join();
    }
    if (postgresDatabases.empty()) {
        std::cout << "No PostgreSQL databases detected. Check nmap output." << std::endl;
    }
    return postgresDatabases;
}


std::vector<DatabaseInfo> DatabaseCrawler::detectMySQLDatabases()
{
   std::vector<DatabaseInfo> ret;
   return ret;
}

std::vector<DatabaseInfo> DatabaseCrawler::detectSqliteDatabases()
{
   std::vector<DatabaseInfo> ret;
   return ret;    
}
