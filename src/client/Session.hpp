//
//  Session.hpp
//  dirtyclient
//
//  Created by Eugene Sturm on 1/26/19.
//

#pragma once

#include "Packet.hpp"
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
    std::vector<Packet> _packetRecvQueue;
    std::vector<Packet> _packetProcessQueue;
    
    std::mutex _packetSendQueueMutex;
    std::vector<Packet> _packetSendQueue;
public:
    Session();
    ~Session();
    
    bool connect(const std::string& address, uint16_t port);
    void update();
    
    void sendMessage(Packet&& packet);
private:
    void listen();
};
