//
//  WorldSocket.cpp
//  dirtyserver
//
//  Created by Eugene Sturm on 1/26/19.
//

#include "WorldSocket.hpp"
#include "WorldSession.hpp"
#include "WorldSessionManager.hpp"
#include <enet/enet.h>
#include <iostream>
#include <array>
#include "Client.hpp"

std::string getAddressString(uint32_t address)
{
    std::array<uint8_t, 4> addrParts {
        (uint8_t)address,
        (uint8_t)(address >> 8),
        (uint8_t)(address >> 16),
        (uint8_t)(address >> 24),
    };
    
    return std::to_string((uint32_t)addrParts[0])
    + "." + std::to_string((uint32_t)addrParts[1])
    + "." + std::to_string((uint32_t)addrParts[2])
    + "." + std::to_string((uint32_t)addrParts[3]);
}

WorldSocket::WorldSocket(WorldSessionManager* sessionManager)
: _sessionManager(sessionManager)
{}

WorldSocket::~WorldSocket()
{
    _isListenThreadRunning = false;
    _listenThread.join();
    
    if (_isInitialized) {
        enet_deinitialize();
    }
}

bool WorldSocket::start()
{
    if (enet_initialize() != 0) {
        std::cerr << "An error occurred while initializing ENet\n";
        return false;
    }
    
    _isInitialized = true;
    
    ENetAddress address;
    address.host = ENET_HOST_ANY;
    address.port = 44951;
    _server = enet_host_create(&address /* the address to bind the server host to */,
                               32      /* allow up to 32 clients and/or outgoing connections */,
                               2      /* allow up to 2 channels to be used, 0 and 1 */,
                               0      /* assume any amount of incoming bandwidth */,
                               0      /* assume any amount of outgoing bandwidth */);
    
    if (_server == nullptr) {
        std::cerr << "An error occurred while trying to create an ENet server host\n";
        return false;
    }
    
    _isListenThreadRunning = true;
    _listenThread = std::thread([this](){ this->listen(); });
    return true;
}

void WorldSocket::processMessage(ENetPeer* peer, WorldPacket&& msg)
{
    switch (msg.messageType()) {
        case MessageType::Auth: {
            auto it = _sessions.find(peer);
            if (it != end(_sessions)) {
                // already have a session
            } else {
                std::shared_ptr<WorldSession> worldSession = std::shared_ptr<WorldSession>(new WorldSession(peer, this));
                _sessions.emplace(peer, worldSession);
                _sessionManager->addSession(worldSession);
                
                AuthResponseMessage authResponse;
                authResponse.sessionId = 0;                                
                
                worldSession->sendPacket(WorldPacket(authResponse));
            }
            break;
        }
        default: {
            auto it = _sessions.find(peer);
            if (it != end(_sessions)) {
                std::shared_ptr<WorldSession>& session = it->second;
                session->recvPacket(std::move(msg));
            } else {
                // no session
            }
            break;
        }
    }
}

void WorldSocket::sendPacket(WorldPacket&& packet, ENetPeer* destination)
{
    std::lock_guard<std::mutex> lock(_sendQueueMutex);
    _sendQueue[destination].emplace_back(packet);
}

bool WorldSocket::isValidMessage(ENetPacket* packet)
{
    return true;
}

void WorldSocket::listen()
{
    while (_isListenThreadRunning) {
        {
            std::lock_guard<std::mutex> lock(_sendQueueMutex);
            std::swap(_processQueue, _sendQueue);
        }
        
        for (const std::pair<ENetPeer*, std::vector<WorldPacket>>& p : _processQueue) {
            ENetPeer* dst = p.first;
            for (const WorldPacket& worldPacket : p.second) {
                ENetPacket* packet = enet_packet_create(worldPacket.data().data(), worldPacket.data().size(),
                                                        ENET_PACKET_FLAG_RELIABLE | ENET_PACKET_FLAG_NO_ALLOCATE);
                enet_peer_send(dst, 0, packet);
            }
        }
        
        ENetEvent event;
        while (enet_host_service(_server, &event, 100) > 0) {
            switch (event.type) {
                case ENET_EVENT_TYPE_CONNECT: {
                    Client client(event.peer);
                    std::cout << "Connect from " << client.host() << ":" << client.port() << std::endl;
                    break;
                }
                case ENET_EVENT_TYPE_RECEIVE: {
                    if (isValidMessage(event.packet)) {
                        WorldPacket packet = WorldPacket(event.packet->data, event.packet->dataLength);
                        enet_packet_destroy(event.packet);
                        
                        std::cout << "Received '" << to_string(packet.messageType()) << "' from " << event.peer->address.host << ":" << event.peer->address.port << std::endl;
                        processMessage(event.peer, std::move(packet));
                    }
                    break;
                }
                case ENET_EVENT_TYPE_DISCONNECT: {
                    std::cout << "Disconnect from " << event.peer->address.host << ":" << event.peer->address.port << std::endl;
                    break;
                }
                case ENET_EVENT_TYPE_NONE: {
                    break;
                }
            }
        }
        
        // wait to clear _process queue til after the packets have been sent since we are using NO_ALLOCATE flag
        _processQueue.clear();
    }
}
