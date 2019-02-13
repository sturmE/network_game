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
    sqlite3pp::query executeQuery(const std::string& queryString);
    int executeCommand(const char* command, std::function<void(sqlite3pp::command&)> delegate = std::function<void(sqlite3pp::command&)>());
    
private:
    void createDbV1();
};
