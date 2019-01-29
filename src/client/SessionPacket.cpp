//
//  SessionPacket.cpp
//  dirtyclient
//
//  Created by Eugene Sturm on 1/26/19.
//

#include "SessionPacket.hpp"
#include <enet/enet.h>

SessionPacket::SessionPacket(ENetPacket* packet, bool shouldDestroy)
: _packet(packet)
, _shouldDestroy(shouldDestroy)
{
}

SessionPacket::~SessionPacket()
{
    if (_shouldDestroy) {
        enet_packet_destroy(_packet);
    }
}

MessageType SessionPacket::messageType() const
{
    const MessageType type = *((MessageType*)_packet->data);
    return type;
}
