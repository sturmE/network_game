//
//  WorldSession.cpp
//  dirtyserver
//
//  Created by Eugene Sturm on 1/26/19.
//

#include "WorldSession.hpp"
#include <enet/enet.h>

WorldSession::WorldSession(ENetPeer* client)
: _client(client)
{
}

void WorldSession::queuePacket(WorldPacket&& packet)
{
    std::lock_guard<std::mutex> lock(_packetQueueMutex);
    _packetRecvQueue.emplace_back(packet);
}

void WorldSession::update()
{
    {
        std::lock_guard<std::mutex> lock(_packetQueueMutex);
        _packetProcessQueue = std::move(_packetRecvQueue);
        _packetRecvQueue.clear();
    }
    
    for (const WorldPacket& packet : _packetProcessQueue) {
        
    }
    
    _packetProcessQueue.clear();
}
