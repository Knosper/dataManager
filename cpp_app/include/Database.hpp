#pragma once
#include <iostream>
#include <string>
#include <vector>

/*TODO: create subclasses like:
    #include <mysql/mysql.h>
    class MySql 
        MYSQL* connection;

    #include <sqlite3.h>
    class SqLlite
        sqlite3* connection;
*/
class t_Database {
public:
    t_Database(const std::string& host, const std::string& user, const std::string& pwd, const std::string& dbName)
        : host(host), user(user), pwd(pwd), dbName(dbName) {}
    
    virtual ~t_Database() {}

    virtual bool connect() = 0;
    virtual void disconnect() = 0;

    virtual bool executeQuery(const std::string& query) = 0;
    virtual std::vector<std::vector<std::string>> getQueryResults() = 0;

protected:
    std::string host;
    std::string user;
    std::string pwd;
    std::string dbName;

    // Results of the last query
    std::vector<std::vector<std::string>> queryResults;

    // Method to clear query results
    void clearQueryResults() {
        queryResults.clear();
    }
};