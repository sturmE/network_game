//
//  World.hpp
//  dirtyserver
//
//  Created by Eugene Sturm on 2/3/19.
//

#pragma once

#include <vector>
#include "Packet.hpp"
#include "WorldServices.hpp"
#include "CharacterDatabase.hpp"

class Session;
using SessionPtr = std::shared_ptr<Session>;

class World
{
private:
    std::vector<SessionPtr> _sessions;
    std::unique_ptr<WorldServices> _services;
    std::unique_ptr<CharacterDatabase> _charDb;
public:
    World();
    
    void addSession(const SessionPtr& session);
    
    void update();
    
    void broadcastPacket(Packet&& packet);
    
    WorldServices* services() { return _services.get(); }
};
