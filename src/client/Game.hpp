//
//  Game.hpp
//  dirtyclient
//
//  Created by Eugene Sturm on 2/3/19.
//

#pragma once

#include <memory>
#include <SDL.h>
#include "Packet.hpp"
#include <vector>

class Connection;
using ConnectionPtr = std::shared_ptr<Connection>;

class Game
{
private:
    ConnectionPtr _connection { nullptr };
public:
    void initialize(ConnectionPtr& connection);    
    void update(const std::vector<SDL_Event>& systemEvents, const std::vector<Packet>& packets, double dt);
    void shutdown();
};
