//
//  WorldSession.cpp
//  dirtyserver
//
//  Created by Eugene Sturm on 1/26/19.
//

#include "WorldSession.hpp"
#include "WorldSocket.hpp"
#include <enet/enet.h>

WorldSession::WorldSession(_ENetPeer* client, WorldSocket* socket)
: _client(client)
, _socket(socket)
{
}

void WorldSession::recvPacket(WorldPacket&& packet)
{
    std::lock_guard<std::mutex> lock(_recvQueueMutex);
    _recvQueue.emplace_back(packet);
}

void WorldSession::sendPacket(WorldPacket&& packet)
{
    std::lock_guard<std::mutex> lock(_sendQueueMutex);
    _sendQueue.emplace_back(packet);
}

void WorldSession::update()
{
    {
        std::lock_guard<std::mutex> lock(_recvQueueMutex);
        std::swap(_processQueue, _recvQueue);
    }
    
    for (const WorldPacket& packet : _processQueue) {
        
    }
    
    _processQueue.clear();
}
