//
//  Map.hpp
//  dirtyserver
//
//  Created by Eugene Sturm on 2/5/19.
//

#pragma once

#include <set>

class Player;

class Map
{
private:
    std::set<Player*> _players;
public:
    Map();
    
    void addPlayer(Player* player);
};
