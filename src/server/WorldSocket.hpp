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
#include <unordered_map>
#include "Packet.hpp"

class WorldSession;
class WorldSessionManager;
struct _ENetPeer;
struct _ENetHost;
struct _ENetPacket;

class WorldSocket
{
private:
    bool _isInitialized { false };
    _ENetHost* _server { nullptr };
    std::thread _listenThread;
    volatile bool _isListenThreadRunning { false };
        
    std::map<_ENetPeer*, std::shared_ptr<WorldSession>> _sessions;
    
    std::mutex _sendQueueMutex;
    std::map<WorldSession*, std::vector<Packet>> _sendQueue;
    
    WorldSessionManager* _sessionManager;
public:
    WorldSocket(WorldSessionManager* sessionManager);
    ~WorldSocket();
    
    bool start();
    void queueSend(Packet&& packet, WorldSession* session);
private:
    void listen();
    void processMessage(_ENetPeer* peer, Packet&& msg);
    bool isValidMessage(_ENetPacket* packet);
};
