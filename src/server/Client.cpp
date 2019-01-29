//
//  Client.cpp
//  dirtyserver
//
//  Created by Eugene Sturm on 1/29/19.
//

#include "Client.hpp"
#include <enet/enet.h>
#include <array>

std::string getAddressString(uint32_t address)
{
    std::array<uint8_t, 4> addrParts {
        (uint8_t)address,
        (uint8_t)(address >> 8),
        (uint8_t)(address >> 16),
        (uint8_t)(address >> 24),
    };
    
    return std::to_string((uint32_t)addrParts[0])
    + "." + std::to_string((uint32_t)addrParts[1])
    + "." + std::to_string((uint32_t)addrParts[2])
    + "." + std::to_string((uint32_t)addrParts[3]);
}

Client::Client(ENetPeer* client)
: _client(client)
, _address(getAddressString(client->address.host))
{
}

const std::string& Client::host() const
{
    return _address;
}

uint16_t Client::port() const
{
    return _client->address.port;
}
