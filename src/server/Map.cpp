//
//  Map.cpp
//  dirtyserver
//
//  Created by Eugene Sturm on 2/5/19.
//

#include "Map.hpp"
#include "Player.hpp"
#include "Session.hpp"

Map::Map()
{
    
}

void Map::addPlayer(Player* player)
{
    if (_players.insert(player).second == false) {
        return;
    }
    
    // send information of everything in Map to player
    for (Player* otherPlayer : _players) {
        if (otherPlayer == player) { continue; }
        
        Packet packet;
        packet << MessageType::CreateObject;
        packet << otherPlayer->guid();
        packet.write(otherPlayer->position().data(), sizeof(float) * 3);
        player->session()->sendPacket(std::move(packet));
    }
    
    // send information of new player to everyone on map
    Packet packet;
    packet << MessageType::CreateObject;
    packet << player->guid();
    packet.write(player->position().data(), sizeof(float) * 3);
    
    auto exclusionPredicate = [player](Player* otherPlayer) -> bool { return otherPlayer == player; };
    broadcastPacket(packet, exclusionPredicate);    
}

void Map::broadcastPacket(const Packet& packet, std::function<bool(Player*)> exclusionPredicate)
{
    for (Player* player : _players) {
        if (exclusionPredicate(player)) { continue; }
        player->session()->sendPacket(packet);
    }
}
