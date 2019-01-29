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
    WorldPacket(std::vector<uint8_t>&& data);
    ~WorldPacket();
    
    MessageType messageType() const;
};
