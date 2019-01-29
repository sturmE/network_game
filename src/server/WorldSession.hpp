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
class WorldSocket;

class WorldSession
{
private:
    std::vector<WorldPacket> _processQueue;
    
    std::mutex _sendQueueMutex;
    std::mutex _recvQueueMutex;
    std::vector<WorldPacket> _sendQueue;
    std::vector<WorldPacket> _recvQueue;
    
    _ENetPeer* _client { nullptr };
    WorldSocket* _socket { nullptr };
public:
    WorldSession(_ENetPeer* client, WorldSocket* socket);
    
    void recvPacket(WorldPacket&& packet);
    void sendPacket(WorldPacket&& packet);
    
    void update();
private:
    
    // friend method with world socket for getting at the sendQueue
};

