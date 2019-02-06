//
//  Player.hpp
//  dirtyserver
//
//  Created by Eugene Sturm on 2/5/19.
//

#pragma once

class Session;
class CharacterDatabase;

struct PlayerCreateInfo
{
    float position[3] { 0, 0, 0 };
};

class Player
{
private:
    float position[3] { 0, 0, 0};
    Session* _session { nullptr };
public:
    Player(const PlayerCreateInfo& creatInfo, Session* session);
    
    void saveToDatabase(CharacterDatabase* db);
};
