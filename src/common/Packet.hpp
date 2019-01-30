//
//  Packet.hpp
//  dirtycommon
//
//  Created by Eugene Sturm on 1/29/19.
//

#pragma once

#include "MessageType.hpp"
#include "Bytebuffer.hpp"

class Packet
{
private:
    ByteStream _data;
public:
    template <typename T>
    Packet(const T& msg)
    {
        msg.pack(_data);
    }
    
    Packet(const uint8_t* data, size_t len);
    
    ~Packet();
    
    MessageType messageType() const;
    uint8_t* data() { return _data.data(); }
    const uint8_t* data() const { return _data.data(); }
    size_t size() const { return _data.size(); }
};


