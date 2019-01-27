//
//  WorldSocket.cpp
//  dirtyserver
//
//  Created by Eugene Sturm on 1/26/19.
//

#include "WorldSocket.hpp"
#include "MessageType.hpp"
#include <iostream>

WorldSession::WorldSession(ENetPeer* client)
: _client(client)
{
}

void WorldSession::queuePacket(WorldPacket&& packet)
{
    std::lock_guard<std::mutex> lock(_packetQueueMutex);
    _packetRecvQueue.emplace_back(packet);
}

void WorldSession::update()
{
    {
        std::lock_guard<std::mutex> lock(_packetQueueMutex);
        _packetProcessQueue = std::move(_packetRecvQueue);
        _packetRecvQueue.clear();
    }
    
    for (const WorldPacket& packet : _packetProcessQueue) {
        
    }
    
    _packetProcessQueue.clear();
}

WorldPacket::WorldPacket(ENetEvent&& event)
: _event(event)
{
}

WorldPacket::~WorldPacket()
{
    enet_packet_destroy(_event.packet);
}

MessageType WorldPacket::messageType() const
{
    const MessageType type = *((MessageType*)_event.packet->data);
    return type;
}

ENetPeer* WorldPacket::clientInfo() const
{
    return _event.peer;
}

WorldSocket::WorldSocket()
{
    if (enet_initialize() != 0) {
        fprintf(stderr, "An error occurred while initializing ENet.\n");
        return;
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
        fprintf(stderr, "An error occurred while trying to create an ENet server host.\n");
        return;
    }
    
    _isListenThreadRunning = true;
    _listenThread = std::thread([this](){ this->listen(); });
}

WorldSocket::~WorldSocket()
{
    _isListenThreadRunning = false;
    _listenThread.join();
    
    if (_isInitialized) {
        enet_deinitialize();
    }
}

void WorldSocket::processMessageQueue()
{
    std::vector<WorldPacket> messages;
    {
        std::lock_guard<std::mutex> lock(_messageQueueMutex);
        if (_messageQueue.empty()) {
            return;
        }
        
        messages = std::move(_messageQueue);
        _messageQueue.clear();
    }
    
    for (WorldPacket& msg : messages) {
        switch (msg.messageType()) {
            case MessageType::Connect: {
                auto it = _sessions.find(msg.clientInfo());
                if (it != end(_sessions)) {
                    // already have a session
                } else {
                    _sessions.emplace(msg.clientInfo(), new WorldSession(msg.clientInfo()));
                }
                break;
            }
            default: {
                auto it = _sessions.find(msg.clientInfo());
                if (it != end(_sessions)) {
                    std::shared_ptr<WorldSession>& session = it->second;
                    session->queuePacket(std::move(msg));
                } else {
                    // no session
                }
                break;
            }
        }
    }
}

bool WorldSocket::isValidMessage(ENetPacket* packet)
{
    return true;
}

void WorldSocket::listen()
{    
    while (_isListenThreadRunning) {
        ENetEvent event;
        while (enet_host_service(_server, &event, 100) > 0) {
            switch (event.type) {
                case ENET_EVENT_TYPE_CONNECT: {
                    std::cout << "Connect from " << event.peer->address.host << ":" << event.peer->address.port << std::endl;
                    break;
                }
                case ENET_EVENT_TYPE_RECEIVE: {
                    std::cout << "Receive from " << event.peer->address.host << ":" << event.peer->address.port << std::endl;
                    if (isValidMessage(event.packet)) {
                        std::lock_guard<std::mutex> lock(_messageQueueMutex);
                        _messageQueue.emplace_back(std::move(event));
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
