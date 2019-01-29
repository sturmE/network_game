//
//  MessageType.hpp
//  dirtycommon
//
//  Created by Eugene Sturm on 1/26/19.
//

#pragma once

#include <stdint.h>
#include <vector>
#include "Bytebuffer.hpp"

enum class MessageType : uint16_t
{
    // Client Messages
    Auth            = 1,
    
    // Server Messages
    AuthResponse    = 32768,
};

const char* to_string(MessageType type);

struct Message
{
    Message(MessageType type) : type(type) {}
    
    const MessageType type;
    
    void pack(std::vector<uint8_t>& buffer)
    {
        buffer.resize(buffer.size() + sizeof(MessageType));
        
    }
};

struct AuthMessage : public Message
{
    AuthMessage() : Message(MessageType::Auth) {}
};

struct AuthResponseMessage : public Message
{
    AuthResponseMessage() : Message(MessageType::AuthResponse) {}
    
    uint64_t sessionId;
    
    void pack(std::vector<uint8_t>& buffer)
    {
        
    }
};



