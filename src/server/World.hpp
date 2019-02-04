//
//  World.hpp
//  dirtyserver
//
//  Created by Eugene Sturm on 2/3/19.
//

#pragma once

#include <vector>
#include "Packet.hpp"

class Session;
using SessionPtr = std::shared_ptr<Session>;

class World
{
private:
    std::vector<SessionPtr> _sessions;
    
public:
    void addSession(const SessionPtr& session);
    
    void update();
    
    void broadcastPacket(Packet&& packet);
};
