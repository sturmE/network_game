//
//  Player.cpp
//  dirtyserver
//
//  Created by Eugene Sturm on 2/5/19.
//

#include "Player.hpp"

Player::Player(const PlayerCreateInfo& createInfo, Session* session)
: Entity(createInfo.guid)
, _session(session)
, _position(createInfo.position)
, _name(createInfo.name)
{
    
}

void Player::saveToDatabase(CharacterDatabase* db)
{
    
}
