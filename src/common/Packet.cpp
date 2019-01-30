//
//  Packet.cpp
//  dirtycommon
//
//  Created by Eugene Sturm on 1/29/19.
//

#include "Packet.hpp"

Packet::Packet(const uint8_t* data, size_t len)
{
    _data.write(data, len);
}

Packet::~Packet()
{}

MessageType Packet::messageType() const
{
    const MessageType type = *((MessageType*)_data.data());
    return type;
}
