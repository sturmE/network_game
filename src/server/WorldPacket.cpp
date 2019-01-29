//
//  WorldPacket.cpp
//  dirtyserver
//
//  Created by Eugene Sturm on 1/26/19.
//

#include "WorldPacket.hpp"

WorldPacket::WorldPacket(std::vector<uint8_t>&& buffer)
: _data(buffer)
{}

WorldPacket::WorldPacket(uint8_t* data, size_t len)
{
    _data.resize(len);
    memcpy(_data.data(), data, len);
}

WorldPacket::~WorldPacket()
{}

MessageType WorldPacket::messageType() const
{
    const MessageType type = *((MessageType*)_data.data());
    return type;
}
