//
//  WorldSession.hpp
//  dirtyserver
//
//  Created by Eugene Sturm on 1/26/19.
//

#pragma once

#include <vector>
#include <mutex>
#include "WorldPacket.hpp"

struct _ENetPeer;

class WorldSession
{
private:
    std::mutex _packetQueueMutex;
    std::vector<WorldPacket> _packetRecvQueue;
    std::vector<WorldPacket> _packetProcessQueue;;
    
    _ENetPeer* _client { nullptr };
public:
    WorldSession(_ENetPeer* client);
    
    void queuePacket(WorldPacket&& packet);
    void sendPacket(WorldPacket&& packet);
    void update();
};

