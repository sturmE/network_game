//
//  Database.cpp
//  dirtyserver
//
//  Created by Eugene Sturm on 2/10/19.
//

#include "Database.hpp"
#include <iostream>

constexpr int32_t kDatabaseVersion = 1;

Database::Database()
{
    _db = sqlite3pp::database("/Users/sturm/test.db");
    sqlite3pp::query query = executeQuery("PRAGMA user_version;");
    
    int32_t version = -1;
    for (sqlite3pp::query::iterator i = query.begin(); i != query.end(); ++i) {
        (*i).getter() >> version;
    }
    
    if (version < kDatabaseVersion) {
        createDbV1();
        
        const std::string commandString = "PRAGMA user_version = "+ std::to_string(kDatabaseVersion) +";";
        executeCommand(commandString.c_str());
    }
}

void Database::createDbV1()
{
    constexpr const char* kCreateCharacterTable =
    "create table t_character ("
    "   id integer primary key autoincrement,"
    "   name string unique,"
    "   pos_x numeric,"
    "   pos_y numeric,"
    "   pos_z numeric"
    ");";
    
    _db.execute(kCreateCharacterTable);
}

sqlite3pp::query Database::executeQuery(const std::string& queryString)
{
    return executeQuery(queryString.c_str());
}

sqlite3pp::query Database::executeQuery(const char* queryString)
{
    std::shared_lock<std::shared_mutex> readLock(_mutex);
    return sqlite3pp::query(_db, queryString);
}

int Database::executeCommand(const char* command, std::function<void(sqlite3pp::command&)> delegate)
{
    std::lock_guard<std::shared_mutex> writeLock(_mutex);
    sqlite3pp::command cmd(_db, command);
    if (delegate) {
        delegate(cmd);
    }
    return cmd.execute();
}
