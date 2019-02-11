//
//  CharacterDatabase.cpp
//  dirtyserver
//
//  Created by Eugene Sturm on 2/5/19.
//

#include "CharacterDatabase.hpp"
#include <iostream>
#include "Database.hpp"


CharacterDatabase::CharacterDatabase(const std::shared_ptr<Database>& db)
: _db(db)
{
}

CharacterDatabase::~CharacterDatabase()
{
}


bool CharacterDatabase::loadPlayer(uint64_t guid, PlayerCreateInfo* infoOut)
{
    if (infoOut == nullptr) {
        return false;
    }
    
    return true;
}

bool CharacterDatabase::savePlayer(Player* player)
{
    
    return true;
}
