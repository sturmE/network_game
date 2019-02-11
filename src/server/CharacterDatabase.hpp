//
//  CharacterDatabase.hpp
//  dirtyserver
//
//  Created by Eugene Sturm on 2/5/19.
//

#pragma once

#include <string>
#include "Player.hpp"

class Database;

class CharacterDatabase
{
private:
    std::shared_ptr<Database> _db { nullptr };
public:
    CharacterDatabase(const std::shared_ptr<Database>& db);
    ~CharacterDatabase();
    
    bool loadPlayer(uint64_t guid, PlayerCreateInfo* infoOut);
    bool savePlayer(Player* player);
private:    
};

