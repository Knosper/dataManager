#include "Macros.hpp"

Macros::Macros():_dataBaseConnection(false), _databaseType(""), _databaseHost(""), _databasePort(0), _databaseName(""), _username(""), _password(""), _status(false)
{
    std::cout << "default Macros created" << std::endl; 
}

Macros::~Macros()
{
    std::cout << "Macros deleted" << std::endl; 
}

bool Macros::connectToDatabase()
{
    // Implement database connection logic here
    // You can use the member variables like _databaseType, _username, etc.
    std::cout << "Connecting to " << _databaseType << " database at " << _databaseHost << ":" << _databasePort << std::endl;
    // If connection is successful
    //_dataBaseConnection = true;
    return _dataBaseConnection;
}