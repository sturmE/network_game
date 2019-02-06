//
//  CharacterDatabase.cpp
//  dirtyserver
//
//  Created by Eugene Sturm on 2/5/19.
//

#include "CharacterDatabase.hpp"
#include <fstream>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

CharacterDatabase::CharacterDatabase()
{
    std::ifstream fileStream("/Users/sturm/test.json", std::fstream::out);
    if (fileStream.is_open()) {
        rapidjson::IStreamWrapper isw(fileStream);
        _json.ParseStream(isw);
    } else {
        _json.SetObject();
    }
    
    
    rapidjson::Value value;
    value.SetInt(10);
    _json.AddMember("test", value, _json.GetAllocator());
    save();
}

CharacterDatabase::~CharacterDatabase()
{
    save();
}

void CharacterDatabase::save()
{
    std::ofstream fileStream("/Users/sturm/test.json", std::ifstream::out | std::ifstream::trunc);
    if (fileStream.is_open()) {
        rapidjson::OStreamWrapper osw(fileStream);
        rapidjson::Writer<rapidjson::OStreamWrapper> writer(osw);
        _json.Accept(writer);
    }
}

bool CharacterDatabase::loadPlayer(const std::string& name, PlayerCreateInfo* infoOut)
{
    if (infoOut == nullptr) {
        return false;
    }
    
    const bool hasName = _json.HasMember(name.c_str());
    if (hasName == false) {
        return false;
    }
    
    // do stuff
    
    return true;
}
