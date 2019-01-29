//
//  Client.hpp
//  dirtyserver
//
//  Created by Eugene Sturm on 1/29/19.
//

#pragma once

#include <string>

class _ENetPeer;

class Client
{
private:
    _ENetPeer* _client { nullptr };
    std::string _address;
public:
    Client(_ENetPeer* client);
    
    const std::string& host() const;
    uint16_t port() const;
};
