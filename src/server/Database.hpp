//
//  Database.hpp
//  dirtyserver
//
//  Created by Eugene Sturm on 2/10/19.
//

#pragma once

#include <sqlite3pp.h>
#include <shared_mutex>

class Database
{
private:
    sqlite3pp::database _db;
    std::shared_mutex _mutex;
public:
    Database();
    sqlite3pp::query executeQuery(const char* queryString);
    int executeCommand(sqlite3pp::command& command);
    int executeCommand(const char* command);
private:
    void createDbV1();
};
