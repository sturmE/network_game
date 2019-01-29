//
//  World.cpp
//  dirtyserver
//
//  Created by Eugene Sturm on 1/26/19.
//

#include "World.hpp"
#include "WorldSession.hpp"
#include "WorldSessionManager.hpp"

World::World(WorldSocket* socket, WorldSessionManager* sessionManager)
: _worldSocket(socket)
, _sessionManager(sessionManager)
{}

void World::update(float dt)
{
    _sessionManager->visitSessions([](WorldSession* session){
        session->update();
    });
}
