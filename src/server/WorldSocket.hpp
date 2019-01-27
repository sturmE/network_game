//
//  WorldSocket.hpp
//  dirtyserver
//
//  Created by Eugene Sturm on 1/26/19.
//

#pragma once

#include <thread>
#include <mutex>
#include <vector>
#include <memory>
#include <map>
#include <enet/enet.h>
#include "MessageType.hpp"

class WorldPacket
{
private:
    ENetEvent _event;
public:
    WorldPacket(ENetEvent&& event);
    ~WorldPacket();
    
    MessageType messageType() const;
    ENetPeer* clientInfo() const;
};

class WorldSession
{
private:
    std::mutex _packetQueueMutex;
    std::vector<WorldPacket> _packetRecvQueue;
    std::vector<WorldPacket> _packetProcessQueue;;
    
    ENetPeer* _client { nullptr };
public:
    WorldSession(ENetPeer* client);
    
    void queuePacket(WorldPacket&& packet);
    void update();
};

class WorldSocket
{
private:
    bool _isInitialized { false };
    ENetHost* _server { nullptr };
    std::thread _listenThread;
    volatile bool _isListenThreadRunning { false };
    
    std::mutex _messageQueueMutex;
    std::vector<WorldPacket> _messageQueue;
    std::map<ENetPeer*, std::shared_ptr<WorldSession>> _sessions;
public:
    WorldSocket();
    ~WorldSocket();
    
    void processMessageQueue();
private:
    void listen();
    bool isValidMessage(ENetPacket* packet);
};
