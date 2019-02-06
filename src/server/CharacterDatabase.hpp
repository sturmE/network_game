//
//  CharacterDatabase.hpp
//  dirtyserver
//
//  Created by Eugene Sturm on 2/5/19.
//

#pragma once

#include <string>
#include "Player.hpp"
#include <rapidjson/document.h>

class CharacterDatabase
{
private:
    rapidjson::Document _json;
public:
    CharacterDatabase();
    ~CharacterDatabase();
    
    bool loadPlayer(const std::string& name, PlayerCreateInfo* infoOut);
private:
    void save();
};

