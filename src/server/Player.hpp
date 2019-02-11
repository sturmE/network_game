//
//  Player.hpp
//  dirtyserver
//
//  Created by Eugene Sturm on 2/5/19.
//

#pragma once

#include "Entity.hpp"
#include <array>
#include <string>

class Session;
class CharacterDatabase;

struct PlayerCreateInfo
{
    uint64_t guid { 0 };
    std::string name;
    std::array<float, 3> position { 0, 0, 0 };
};

class Player : public Entity
{
private:
    std::array<float, 3> _position { 0, 0, 0};
    Session* _session { nullptr };
    std::string _name;
public:
    Player(const PlayerCreateInfo& createInfo, Session* session);
    
    void saveToDatabase(CharacterDatabase* db);
    
    const std::array<float, 3>& position() const { return _position; }
    Session* session() { return _session; }
    const std::string& name() const { return _name; }
};
