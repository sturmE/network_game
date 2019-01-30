//
//  WorldSession.hpp
//  dirtyserver
//
//  Created by Eugene Sturm on 1/26/19.
//

#pragma once

#include <vector>
#include <mutex>
#include "Packet.hpp"

struct _ENetPeer;
class WorldSocket;

class WorldSession
{
private:
    std::vector<Packet> _processQueue;
    
    std::mutex _sendQueueMutex;
    std::mutex _recvQueueMutex;
    std::vector<Packet> _sendQueue;
    std::vector<Packet> _recvQueue;
    
    _ENetPeer* _client { nullptr };
    WorldSocket* _socket { nullptr };
public:
    WorldSession(_ENetPeer* client, WorldSocket* socket);
    
    void queueRecv(Packet&& packet);
    void queueSend(Packet&& packet);
    
    void update();
    
    _ENetPeer* clientInfo() { return _client; }
private:
    
    // friend method with world socket for getting at the sendQueue
};

