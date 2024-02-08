#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <mysql/mysql.h>
#include <sqlite3.h>

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

class MySql : public t_Database {
public:
    MySql(const std::string& host, const std::string& user, const std::string& pwd, const std::string& dbName);
        //: t_Database(host, user, pwd, dbName), connection(nullptr) {}

    ~MySql();

    bool connect() override;

    void disconnect() override;

    bool executeQuery(const std::string& query) override;

    std::vector<std::vector<std::string>> getQueryResults();

private:
    MYSQL* connection;
};

class SqLite : public t_Database {
public:
    SqLite(const std::string& dbName);
        //: t_Database("", "", "", dbName), connection(nullptr) {}

    ~SqLite();

    bool connect() override;

    void disconnect() override;

    bool executeQuery(const std::string& query);

    std::vector<std::vector<std::string>> getQueryResults() override;

private:
    sqlite3* connection;
};
