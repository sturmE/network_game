//
//  SessionPacket.hpp
//  dirtyclient
//
//  Created by Eugene Sturm on 1/26/19.
//

#pragma once

#include "MessageType.hpp"

struct _ENetPacket;

class SessionPacket
{
private:
    _ENetPacket* _packet { nullptr };
    bool _shouldDestroy { true };
public:
    SessionPacket(_ENetPacket* packet, bool shouldDestroy = true);
    ~SessionPacket();
    
    MessageType messageType() const;
    _ENetPacket* packet() const  { return _packet; }
};
