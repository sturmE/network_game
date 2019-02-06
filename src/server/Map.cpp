//
//  Map.cpp
//  dirtyserver
//
//  Created by Eugene Sturm on 2/5/19.
//

#include "Map.hpp"


void Map::addPlayer(Player* player)
{
    if (_players.insert(player).second == false) {
        return;
    }
    
    // send information of everything in Map to player
    for (Player* otherPlayer : _players) {
        if (otherPlayer == player) { continue; }
        
        // send create object messages
        // -- guid
        // -- position
        // -- movement info
        
    }
    
    // send information of new player to everything in map
    
}
