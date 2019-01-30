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

void WorldSocket::processMessage(ENetPeer* peer, Packet&& msg)
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
                
                worldSession->queueSend(Packet(authResponse));
            }
            break;
        }
        default: {
            auto it = _sessions.find(peer);
            if (it != end(_sessions)) {
                std::shared_ptr<WorldSession>& session = it->second;
                session->queueRecv(std::move(msg));
            } else {
                // no session
            }
            break;
        }
    }
}


bool WorldSocket::isValidMessage(ENetPacket* packet)
{
    return true;
}

void WorldSocket::queueSend(Packet&& packet, WorldSession* session)
{
    std::lock_guard<std::mutex> lock(_sendQueueMutex);
    _sendQueue[session].emplace_back(packet);
}

static void rawr(ENetPacket* packet) {
    printf("boo\n");
}

void WorldSocket::listen()
{
    std::map<WorldSession*, std::vector<Packet>> sendQueue;
    while (_isListenThreadRunning) {
        sendQueue.clear();
        {
            std::lock_guard<std::mutex> lock(_sendQueueMutex);
            sendQueue = std::move(_sendQueue);
            _sendQueue.clear();
        }
        
        for (const std::pair<WorldSession*, std::vector<Packet>>& p : sendQueue) {
            ENetPeer* dst = p.first->clientInfo();
            for (const Packet& packet : p.second) {
                std::cout << "Sending '" << to_string(packet.messageType()) << "' to " << dst->address.host << ":" << dst->address.port << std::endl;
                ENetPacket* enetPacket = enet_packet_create(packet.data(), packet.size(),
                                                        ENET_PACKET_FLAG_RELIABLE | ENET_PACKET_FLAG_NO_ALLOCATE);
                enetPacket->freeCallback = rawr;
                enet_peer_send(dst, 0, enetPacket);
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
                        
                        Packet packet = Packet(event.packet->data, event.packet->dataLength);
                        enet_packet_destroy(event.packet);
                        
                        std::cout << "Received '" << to_string(packet.messageType()) << "' from " << event.peer->address.host << ":" << event.peer->address.port << std::endl;
                        processMessage(event.peer, std::move(packet));
                    } else {
                        std::cout << "Dropped packet" << std::endl;
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
    }
}
