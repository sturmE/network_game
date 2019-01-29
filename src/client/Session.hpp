//
//  Session.hpp
//  dirtyclient
//
//  Created by Eugene Sturm on 1/26/19.
//

#pragma once

#include "SessionPacket.hpp"
#include <thread>
#include <mutex>
#include <vector>

class _ENetHost;
class _ENetPeer;

class Session
{
private:
    _ENetHost* _client { nullptr };
    _ENetPeer* _server { nullptr };
    
    volatile bool _isSessionThreadRunning { false };
    std::thread _sessionThread;
    
    std::mutex _packetRecvQueueMutex;
    std::vector<SessionPacket> _packetRecvQueue;
    std::vector<SessionPacket> _packetProcessQueue;
    
    std::mutex _packetSendQueueMutex;
    std::vector<SessionPacket> _packetSendQueue;    
public:
    Session();
    ~Session();
    
    bool connect(const std::string& address, uint16_t port);
    void update();
    
    void sendMessage(SessionPacket&& packet);
private:
    void listen();
};
