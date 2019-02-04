//
//  Game.cpp
//  dirtyclient
//
//  Created by Eugene Sturm on 2/3/19.
//

#include "Game.hpp"
#include "Connection.hpp"

void Game::initialize(ConnectionPtr& connection)
{
    _connection = connection;
}

void Game::update(const std::vector<SDL_Event>& systemEvents, const std::vector<Packet>& packets, double dt)
{
    
}

void Game::shutdown()
{
    
}
