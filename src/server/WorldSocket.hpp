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
#include "WorldPacket.hpp"

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
    
    WorldSessionManager* _sessionManager;
public:
    WorldSocket(WorldSessionManager* sessionManager);
    ~WorldSocket();
    
    bool start();
private:
    void listen();
    void processMessage(WorldPacket&& msg);
    bool isValidMessage(_ENetPacket* packet);
};
