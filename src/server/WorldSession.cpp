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

void WorldSession::queueRecv(Packet&& packet)
{
    std::lock_guard<std::mutex> lock(_recvQueueMutex);
    _recvQueue.emplace_back(packet);
}

void WorldSession::queueSend(Packet&& packet)
{
    _socket->queueSend(std::move(packet), this);
}

void WorldSession::update()
{
    {
        std::lock_guard<std::mutex> lock(_recvQueueMutex);
        std::swap(_processQueue, _recvQueue);
    }
    
    for (const Packet& packet : _processQueue) {
        
    }
    
    _processQueue.clear();
}


