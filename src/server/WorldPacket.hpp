//
//  WorldPacket.hpp
//  dirtyserver
//
//  Created by Eugene Sturm on 1/26/19.
//

#pragma once

#include "MessageType.hpp"

class WorldPacket
{
private:
    std::vector<uint8_t> _data;
public:
    template <typename T>
    WorldPacket(const T& msg)
    {
        msg.pack(_data);
    }
    
    WorldPacket(std::vector<uint8_t>&& data);
    WorldPacket(uint8_t* data, size_t len);
    ~WorldPacket();
    
    MessageType messageType() const;
    std::vector<uint8_t>& data() { return _data; }
    const std::vector<uint8_t>& data() const { return _data; }
};
