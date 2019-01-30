//
//  Session.cpp
//  dirtyclient
//
//  Created by Eugene Sturm on 1/26/19.
//

#include "Session.hpp"
#include "Bytebuffer.hpp"
#include <enet/enet.h>
#include <iostream>

Session::Session()
{
}

Session::~Session()
{
    if (_client != nullptr && _server != nullptr) {
        _isSessionThreadRunning = false;
        _sessionThread.join();
        
        enet_peer_disconnect(_server, 0);
        
        ENetEvent event;
        while (enet_host_service(_client, &event, 10000) > 0) {
            switch (event.type) {
                case ENET_EVENT_TYPE_RECEIVE:
                    enet_packet_destroy(event.packet);
                    break;
                case ENET_EVENT_TYPE_DISCONNECT:
                    std::cout << "Disconnection succeeded\n";
                    break;
                default:
                    std::cout << "unhandled event type\n";
                    break;
            }
        }
        enet_peer_reset(_server);
    }
}

bool Session::connect(const std::string& addr, uint16_t port)
{
    _client = enet_host_create(NULL /* create a client host */,
                               1 /* only allow 1 outgoing connection */,
                               2 /* allow up 2 channels to be used, 0 and 1 */,
                               0 /* assume any amount of incoming bandwidth */,
                               0 /* assume any amount of incoming bandwidth */);
    if (_client == nullptr) {
        std::cerr << "An error occurred while trying to create an ENet client host\n";
        return false;
    }
    
    ENetAddress address;
    ENetEvent event;
    
    enet_address_set_host(&address, addr.c_str());
    address.port = port;
    _server = enet_host_connect(_client, &address, 2, 0);
    if (_server == nullptr) {
        std::cerr << "No available peers for initiating an ENet connection\n";
        return false;
    }
    
    // wait for connection
    if (enet_host_service(_client, &event, 5000) > 0 && event.type == ENET_EVENT_TYPE_CONNECT) {
        std::cout << "Connection to server succeeded\n";
    } else {
        enet_peer_reset(_server);
        _server = nullptr;
        std::cout << "Connection to server failed\n";
        return false;
    }
    
    _isSessionThreadRunning = true;
    _sessionThread = std::thread([this](){ this->listen(); });
    
    sendMessage(Packet(AuthMessage()));
    
    return true;
}

void Session::listen()
{
    while (_isSessionThreadRunning) {
        
        {
            std::lock_guard<std::mutex> lock(_packetSendQueueMutex);
            for (Packet& packet : _packetSendQueue) {
                ENetPacket* enetPacket = enet_packet_create(packet.data(), packet.size(), ENET_PACKET_FLAG_RELIABLE);
                std::cout << "Sending '" << to_string(packet.messageType()) << std::endl;
                enet_peer_send(_server, 0, enetPacket);
            }
        }
        
        ENetEvent event;
        while (enet_host_service(_client, &event, 100) > 0) {
            switch (event.type) {
                case ENET_EVENT_TYPE_RECEIVE: {
                    Packet packet(event.packet->data, event.packet->dataLength);
                    enet_packet_destroy(event.packet);
                    std::cout << "Received '" << to_string(packet.messageType()) << std::endl;
                    std::lock_guard<std::mutex> lock(_packetRecvQueueMutex);
                    _packetRecvQueue.emplace_back(std::move(packet));
                    break;
                }
                default: {
                    std::cout << "Received unexpected message type\n";
                    break;
                }
            }
        }
        
        _packetSendQueue.clear();
    }
}

void Session::update()
{
//    ChatMessage chatmsg;
//    chatmsg.contents = "rawrrawrarawr";
//    
//    ByteStream bytestream;
//    chatmsg.pack(bytestream);
//    
//    sendMessage(Packet(enet_packet_create(bytestream.data(), bytestream.size(), ENET_PACKET_FLAG_RELIABLE), false));
}

void Session::sendMessage(Packet&& msg)
{
    std::lock_guard<std::mutex> lock(_packetSendQueueMutex);
    _packetSendQueue.emplace_back(msg);
}

