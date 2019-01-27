//
//  main.cpp
//  dirtyjam
//
//  Created by Eugene Sturm on 1/25/19.
//

#include <enet/enet.h>
#include <string>
#include <vector>
#include "Event.h"

#include "WorldSocket.hpp"


void other()
{
    WorldSocket socket;
    
    while (true) {
        socket.processMessageQueue();
    }
}

struct PeerData
{
    PeerData(uint32_t id) : peerId(id) {}
    
    const uint32_t peerId { 0 };
};

int main(int argc, char** argv)
{
    other();
    
    uint32_t peerIdKey = 1;
    if (enet_initialize () != 0) {
        fprintf (stderr, "An error occurred while initializing ENet.\n");
        return EXIT_FAILURE;
    }
    atexit(enet_deinitialize);
    
    ENetAddress address;
    ENetHost* server;
    address.host = ENET_HOST_ANY;
    address.port = 44951;
    server = enet_host_create (& address /* the address to bind the server host to */,
                               32      /* allow up to 32 clients and/or outgoing connections */,
                               2      /* allow up to 2 channels to be used, 0 and 1 */,
                               0      /* assume any amount of incoming bandwidth */,
                               0      /* assume any amount of outgoing bandwidth */);
    if (server == NULL) {
        fprintf (stderr,
                 "An error occurred while trying to create an ENet server host.\n");
        exit (EXIT_FAILURE);
    }
    
    std::vector<ENetPeer*> peers;
    
    // for now, was thinking the server just relays all messages from peer to all other peers
    printf("server is running...\n");
    while (true) {
        ENetEvent event;
        
        while (enet_host_service(server, & event, 1000) > 0)
        {
            switch (event.type)
            {
                case ENET_EVENT_TYPE_CONNECT: {
                    printf("A new client connected from %x:%u.\n", event.peer->address.host, event.peer->address.port);
                    /* Store any relevant client information here. */
                    PeerData* peerData = new PeerData(peerIdKey++);
                    event.peer->data = peerData;
                    
                    std::vector<std::pair<uint64_t, EntityType>> entities;
                    for (ENetPeer* peer : peers) {
                        entities.emplace_back(((PeerData*)peer->data)->peerId, EntityType::Player);
                    }
                    
                    std::vector<uint8_t> buffer;
                    event::serialize(OnConnectEvent(peerData->peerId, std::move(entities)), buffer);
                    ENetPacket* packet = enet_packet_create(buffer.data(), buffer.size(), ENET_PACKET_FLAG_RELIABLE);                    
                    enet_peer_send(event.peer, 0, packet);                                        
                    peers.emplace_back(event.peer);
                    break;
                }
                case ENET_EVENT_TYPE_RECEIVE: {
                    Event* baseEvent = nullptr;
                    baseEvent = reinterpret_cast<Event*>(event.packet->data);
                    printf ("Received event:%s from peer:%d\n", to_string(baseEvent->type).data(), ((PeerData*)event.peer->data)->peerId);
                    
                    // broadcast packet to all other peers
                    for (ENetPeer* peer : peers) {
                        if (peer != event.peer) {
                            enet_peer_send(peer, 0, event.packet);
                        }
                    }
                    break;
                }
                case ENET_EVENT_TYPE_DISCONNECT: {
                    printf("%d disconnected\n", ((PeerData*)event.peer->data)->peerId);
                    delete (PeerData*)event.peer->data;
                    peers.erase(std::remove(begin(peers), end(peers), event.peer), end(peers));
                    break;
                }
                default: {
                    printf("unhandled event type:%d\n", event.type);
                    break;
                }
            }
        }
    }
}

