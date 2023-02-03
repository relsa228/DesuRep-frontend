#include "databaseService.h"

#include <iostream>

bool auth(std::string username, std::string password) {
    sqlite3* db;
    sqlite3_stmt* stmt;
    sqlite3_open("desunetdb.db", &db);

    std::string query =  "SELECT id FROM \"users\" WHERE uname='" + username + "' AND pass='" + password + "'";
    sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, 0);
    sqlite3_step(stmt);
    auto id = sqlite3_column_int(stmt, 0);
    sqlite3_close(db);    
    if (id == 0)
        return false;
    return true;
}

std::vector<std::string> getListOfUsers() {
    std::vector<std::string> result;
    return result;
}

std::vector<std::string> getChat(int getterId, int senderId) {
    std::vector<std::string> result;
    return result;
}

void saveMsg(int getterId, int senderId, std::string msg) {
    std::string query =  "INSERT INTO \"msgs\" VALUES (" + std::to_string(senderId) + ", " + std::to_string(getterId) + ", '" + msg + "');";
}

bool saveUsr(std::string username, std::string password) {
    sqlite3* db;
    sqlite3_stmt* stmt;
    sqlite3_open("desunetdb.db", &db);

    std::string query = "INSERT INTO \"users\" VALUES ('" + username +"', '" + password +"', NULL);";
    int rc = sqlite3_exec(db, query.c_str(), NULL, NULL, NULL);

    sqlite3_close(db);
    if (rc != SQLITE_OK)
        return false;
    return true;
}