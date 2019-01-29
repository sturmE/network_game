//
//  World.hpp
//  dirtyserver
//
//  Created by Eugene Sturm on 1/26/19.
//

#pragma once

#include <vector>

class WorldSession;
class WorldSocket;
class WorldSessionManager;

class World
{
private:
    WorldSocket* _worldSocket { nullptr };
    WorldSessionManager* _sessionManager { nullptr };
    std::vector<std::shared_ptr<WorldSession>> _sessions;
public:
    World(WorldSocket* socket, WorldSessionManager* sessionManager);
    
    void update(float dt);
};
