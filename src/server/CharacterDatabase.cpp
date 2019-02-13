//
//  CharacterDatabase.cpp
//  dirtyserver
//
//  Created by Eugene Sturm on 2/5/19.
//

#include "CharacterDatabase.hpp"
#include <iostream>
#include "Database.hpp"
#include <sstream>


CharacterDatabase::CharacterDatabase(const std::shared_ptr<Database>& db)
: _db(db)
{
}

CharacterDatabase::~CharacterDatabase()
{
}


bool CharacterDatabase::loadPlayer(const std::string& name, PlayerCreateInfo* infoOut)
{
    if (infoOut == nullptr) {
        return false;
    }
    
    std::stringstream ss;
    ss << "select * from t_character where name like '" << name << "';";
    
    sqlite3pp::query query = _db->executeQuery(ss.str());
    auto q = (*query.begin());    
    q.getter() >> (int64_t&)infoOut->guid >> infoOut->name >> infoOut->position[0] >> infoOut->position[1] >> infoOut->position[2];

    return true;
}

bool CharacterDatabase::savePlayer(Player* player)
{
    auto delegate = [player](sqlite3pp::command& cmd)
    {
        cmd.bind(1, (int64_t)player->guid());
        cmd.bind(2, player->name(), sqlite3pp::nocopy);
        cmd.bind(3, player->position()[0]);
        cmd.bind(4, player->position()[1]);
        cmd.bind(5, player->position()[2]);        
    };
    
    int result = _db->executeCommand("insert into t_character (id, name, pos_x, pos_y, pos_z) VALUES (?, ?, ?, ?, ?)", delegate);
    return result > 0;
}

uint64_t CharacterDatabase::getMaxGuid()
{
    sqlite3pp::query query = _db->executeQuery("select max(id) from t_character");
    int64_t guid = 0;
    for (sqlite3pp::query::iterator i = query.begin(); i != query.end(); ++i) {
        (*i).getter() >> guid;
    }
    return guid;
}
