//
//  Game.cpp
//  dirtyclient
//
//  Created by Eugene Sturm on 2/3/19.
//

#include "Game.hpp"
#include "Connection.hpp"

void Game::initialize(gfx::RenderDevice* device, gfx::Swapchain* swapchain, ConnectionPtr& connection)
{
    _device = device;
    _swapchain = swapchain;
    _connection = connection;
}

void Game::update(const std::vector<SDL_Event>& systemEvents, const std::vector<Packet>& packets, double dt)
{
    
}

void Game::shutdown()
{
    
}
