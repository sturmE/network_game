//
//  Network.h
//  dirtyclient
//
//  Created by Eugene Sturm on 1/25/19.
//

#pragma once

#include <enet/enet.h>
#include <vector>

class Network
{
private:
    std::vector<uint8_t> _buffer;
    ENetPeer* _peer;
public:
    Network(ENetPeer* peer) : _peer(peer) {}
    
    template <typename T>
    void sendMessage(const T& msg);
};

template <typename T>
void Network::sendMessage(const T& msg)
{
    _buffer.clear();
    msg.serialize(_buffer);
    
    ENetPacket* packet = enet_packet_create(_buffer.data(), _buffer.size(), ENET_PACKET_FLAG_RELIABLE);
    enet_peer_send(_peer, 0, packet);
}
