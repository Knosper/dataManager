//Database.cpp
#include "Database.hpp"

MySql::MySql(const std::string& host, const std::string& user, const std::string& pwd, const std::string& dbName): t_Database(host, user, pwd, dbName), connection(nullptr)
{
    std::cout << "default Database created" << std::endl;
}

MySql::~MySql() {
    disconnect();
    std::cout << "default Database deleted" << std::endl;
}

bool MySql::connect() {
    connection = mysql_init(nullptr);
    if (connection == nullptr) {
        std::cerr << "Failed to initialize MySQL connection" << std::endl;
        return false;
    }

    if (mysql_real_connect(connection, host.c_str(), user.c_str(), pwd.c_str(), dbName.c_str(), 0, nullptr, 0) == nullptr) {
        std::cerr << "Failed to connect to MySQL database: " << mysql_error(connection) << std::endl;
        return false;
    }

    return true;
}

void MySql::disconnect() {
    if (connection != nullptr) {
        mysql_close(connection);
        connection = nullptr;
    }
}

bool MySql::executeQuery(const std::string& query) {
    clearQueryResults();

    if (mysql_query(connection, query.c_str()) != 0) {
        std::cerr << "Failed to execute MySQL query: " << mysql_error(connection) << std::endl;
        return false;
    }

    MYSQL_RES* result = mysql_store_result(connection);
    if (result == nullptr) {
        std::cerr << "Failed to get MySQL query result: " << mysql_error(connection) << std::endl;
        return false;
    }

    int numFields = mysql_num_fields(result);
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result)) != nullptr) {
        std::vector<std::string> rowData;
        for (int i = 0; i < numFields; i++) {
            rowData.push_back(row[i] != nullptr ? row[i] : "");
        }
        queryResults.push_back(rowData);
    }

    mysql_free_result(result);
    return true;
}

std::vector<std::vector<std::string>> MySql::getQueryResults() {
    return queryResults;
}

SqLite::SqLite(const std::string& dbName)
    : t_Database("", "", "", dbName), connection(nullptr) {}

SqLite::~SqLite() {
    disconnect();
}

bool SqLite::connect() {
    if (sqlite3_open(dbName.c_str(), &connection) != SQLITE_OK) {
        std::cerr << "Failed to connect to SQLite database: " << sqlite3_errmsg(connection) << std::endl;
        return false;
    }

    return true;
}

void SqLite::disconnect() {
    if (connection != nullptr) {
        sqlite3_close(connection);
        connection = nullptr;
    }
}

bool SqLite::executeQuery(const std::string& query) {
    clearQueryResults();

    sqlite3_stmt* statement;
    if (sqlite3_prepare_v2(connection, query.c_str(), -1, &statement, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare SQLite query: " << sqlite3_errmsg(connection) << std::endl;
        return false;
    }

    int result = sqlite3_step(statement);
    while (result == SQLITE_ROW) {
        std::vector<std::string> rowData;
        int numColumns = sqlite3_column_count(statement);
        for (int i = 0; i < numColumns; i++) {
            const char* columnValue = reinterpret_cast<const char*>(sqlite3_column_text(statement, i));
            rowData.push_back(columnValue != nullptr ? columnValue : "");
        }
        queryResults.push_back(rowData);

        result = sqlite3_step(statement);
    }

    sqlite3_finalize(statement);
    return true;
}

std::vector<std::vector<std::string>> SqLite::getQueryResults()
{
    return queryResults;
}
